/**
	Menu functions
	Orig. by: Herr Muskelprotze
	by: Emmanuel Utomi
	
**/

#define do_toggle(x) \
	if(x) x=false;\
	else x=true;\
	reset_menu();

void print(char *text)
{
PRINT_STRING_WITH_LITERAL_STRING_NOW("string", text, 2500, 1);
}

void draw_title(float x, float y, float width, float height, uint r, uint g, uint b, uint a, char *val){
#ifdef PC
	if (!IS_FONT_LOADED(7))
	{
		LOAD_TEXT_FONT(7);
	}
	SET_TEXT_FONT(7);
#else
	if (!IS_FONT_LOADED(6))
	{
		LOAD_TEXT_FONT(6);
	}
	SET_TEXT_FONT(6);
#endif
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(1, 0, 0, 0, 255);
	SET_TEXT_PROPORTIONAL(1);
	SET_TEXT_WRAP(0.0000, 1.0000);	

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(1);
	SET_TEXT_RIGHT_JUSTIFY(0);
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, "STRING", val);
}

void set_up_draw(int type, float width, float height, uint r, uint g, uint b, uint a){

	SET_TEXT_FONT(0);

	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(0, 0, 0, 0, 255);

	if (type == 1)
	{
		SET_TEXT_BACKGROUND(1);
	}
	else if (type == 2)
	{
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	}
	else if (type == 3)
	{
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
	}

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_PROPORTIONAL(1);

	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(0);
	SET_TEXT_RIGHT_JUSTIFY(0);

}

void draw_text(char *gxtName, float x, float y, char *val){
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, gxtName, val);
	return;
}	
	
void draw_number(char *gxtName, float x, float y, int val){
	DISPLAY_TEXT_WITH_NUMBER(x, y, gxtName, val);
	return;
}

void menu_startup(void){
	menu_level = 0;
	item_select = 1;
	
	CLEAR_PRINTS();
	CLEAR_HELP();
	
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphone");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("spcellphone");
	
	WAIT(200);
	
	menu_setup();
	show_menu = true;
}

void menu_shutdown(void){
	menu_level = 0;
	item_select = 1;
	show_menu = false;
	
	reset_menu();
	
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("addon_loader");
	
	WAIT(200);
	if(IS_NETWORK_SESSION()){
		REQUEST_SCRIPT("mpcellphone");
		while(!HAS_SCRIPT_LOADED("mpcellphone")) WAIT(0);
		START_NEW_SCRIPT("mpcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("mpcellphone");
	}
	else{
		REQUEST_SCRIPT("spcellphone");
		while(!HAS_SCRIPT_LOADED("spcellphone")) WAIT(0);
		START_NEW_SCRIPT("spcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("spcellphone");				
	}	
}
	
void create_big_explosion(float fX,float fY,float fZ){
	ADD_EXPLOSION(fX,fY,fZ + 12.5,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY + 30.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY - 40.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 12.5,fY + 12.5,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX + 25.0,fY + 25.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 12.5,fY - 12.5,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 25.0,fY - 25.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);

}

void teleport_char(Ped pPed,float x,float y,float z){
	if(IS_CHAR_IN_ANY_CAR(pPed)){
		int pveh,nvid,tick;
		GET_CAR_CHAR_IS_USING(pPed,&pveh);
		GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
		REQUEST_CONTROL_OF_NETWORK_ID(nvid);
		while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
			tick++;
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			if(tick >= 200){
				print("Error");
				return;
			}
			WAIT(0);
		}
		SET_CAR_COORDINATES(pveh,x,y,z);
	}
	else{
		SET_CHAR_COORDINATES(pPed,x,y,z);
		SET_GAME_CAM_HEADING(0.0);
		LOAD_ALL_OBJECTS_NOW();
	}
	REQUEST_COLLISION_AT_POSN(x,y,z);
}

void create_throwable_object(uint model){
	int obj = 0;
	float fX,fY,fZ;
	GET_CHAR_COORDINATES(pPlayer,&fX,&fY,&fZ);
	CREATE_OBJECT(model,fX,fY,fZ,&obj,true);
	SET_OBJECT_QUATERNION(obj,0,0,0,0);
	SET_OBJECT_INVINCIBLE(obj,false);
	FREEZE_OBJECT_POSITION(obj,false);
	SET_OBJECT_DYNAMIC(obj,true);
	SET_OBJECT_AS_STEALABLE(obj,true);
	SET_OBJECT_COLLISION(obj,true);
}

void spawn_car(uint model){
	int pveh,driver;
	float x,y,z,h,s;
	bool speed = false;
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
	GET_CHAR_HEADING(pPlayer,&h);
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		GET_CAR_SPEED(pveh,&s);
		speed = true;
		GET_DRIVER_OF_CAR(pveh,&driver);
		WARP_CHAR_FROM_CAR_TO_COORD(pPlayer,x,y,z);
		if(!DOES_CHAR_EXIST(driver) || pPlayer == driver || !IS_NETWORK_SESSION()){
			DELETE_CAR(&pveh);
			MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
		}
	}
	CREATE_CAR(model,x,y,z,&pveh,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
	SET_CAR_ENGINE_ON(pveh,true,true);
	WARP_CHAR_INTO_CAR(pPlayer,pveh);
	SET_CAR_HEADING(pveh,h);
	if(speed)
		SET_CAR_FORWARD_SPEED(pveh,s);
	return;
}
	
void menu_functions(void){
	if(menu_level == 1){
		if(last_selected[0] == 1){
			if(item_select == 3){
				SET_CHAR_HEALTH(pPlayer,500);
				ADD_ARMOUR_TO_CHAR(pPlayer,100);
				return;
			}
			if(item_select == 4){
				do_toggle(godmode);
				return;
			}
			if(item_select == 5){
				do_toggle(neverwanted);
				if(neverwanted)
					SET_MAX_WANTED_LEVEL(0);
				else
					SET_MAX_WANTED_LEVEL(6);
				return;
			}
			if(item_select == 6){
				do_toggle(pprotection);
				FREEZE_CHAR_POSITION(pPlayer,false);
				return;
			}
			if(item_select == 7){
				do_toggle(superrun);
				return;
			}
			if(item_select == 8){
				do_toggle(superjump);
				return;
			}
			if(item_select == 9){
				do_toggle(forcefield);
				return;
			}
		}
		if(last_selected[0] == 2){
			if(item_select == 2){
				do_toggle(vhelper);
				return;
			}
			if(item_select == 3){
				print("Removed at the request of DannyDarthTk");
				//do_toggle(flywalls);
				return;
			}
			if(item_select == 4){
				do_toggle(carsonground);
				return;
			}
			if(item_select == 5){
				do_toggle(nfs);
				return;
			}
			if(item_select == 6){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					float x,y,z;
					GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
					teleport_char(pPlayer,0.0,4000.0,0.0);
					WAIT(0);
					teleport_char(pPlayer,x,y,z);
				}
				return;
			}
			if(item_select == 7){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					Vehicle pveh;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					FIX_CAR(pveh);
					SET_VEHICLE_DIRT_LEVEL(pveh,0.0);
					print("Vehicle fixed & washed!");
				}
				return;
			}
			if(item_select == 8){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					uint lock;
					Vehicle pveh;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_CAR_DOOR_LOCK_STATUS(pveh,&lock);
					if(lock == VEHICLE_DOOR_UNLOCKED){
						LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_LOCKED_BOTH_SIDES);
						print("Doors locked!");
					}
					else{
						LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_UNLOCKED);
						print("Doors unlocked!");
					}
				}
				return;
			}
			if(item_select == 9){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					Vehicle pveh;
					Ped driver;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_DRIVER_OF_CAR(pveh,&driver);
					if(driver == pPlayer){
						DELETE_CAR(&pveh);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
					else print("You must be the driver of this vehicle");
				}
				return;
			}
			if(item_select == 10){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					Vehicle pveh;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					SET_CAR_ON_GROUND_PROPERLY(pveh);
				}
				return;
			}
		}
		if(last_selected[0] == 3){
			if(item_select == 2){
				do_toggle(ammo);
				return;
			}
		}
		if(last_selected[0] == 4){
			if(item_select == 1){
				if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
					Vector3 pos;
					float z;
					GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&pos);
					teleport_char(pPlayer,pos.x,pos.y,0.0);
					
					GET_GROUND_Z_FOR_3D_COORD(pos.x,pos.y,1000,&z);
					WAIT(0);
					teleport_char(pPlayer,pos.x,pos.y,z);
				}
				else print("You need to set a waypoint!");
				
				return;
			}
			if(item_select == 2){
				teleport_char(pPlayer,2175.3516,761.2235,30.0);
				return;
			}
			if(item_select == 3){
				teleport_char(pPlayer,1100.5,-747.0,7.39);
				return;
			}
			if(item_select == 4){
				teleport_char(pPlayer,-178.2,582.6,126.85);
				return;
			}
			if(item_select == 5){
				teleport_char(pPlayer,-2476.0,942.7,1100.0);
				return;
			}
			if(item_select == 6){
				teleport_char(pPlayer,-236.0,795.9,6.20);
				return;
			}
			if(item_select == 7){
				teleport_char(pPlayer,-415.17,1463.54,39.0);
				return;
			}
			if(item_select == 8){
				teleport_char(pPlayer,-279.77,-99.66,386.791);
				return;
			}
			if(item_select == 9){
				teleport_char(pPlayer,-1079.8,-469.7,2.62);
				return;
			}
			if(item_select == 10){
				teleport_char(pPlayer,1375.8765,197.4544,48.0);
				return;
			}
			if(item_select == 11){
				teleport_char(pPlayer,-532.681,1273.3307,105.65);
				return;
			}
			if(item_select == 12){
				teleport_char(pPlayer,55.3537,1125.3387,2.4527);
				return;
			}
			if(item_select == 13){
				teleport_char(pPlayer,104.13,856.53,45.58);
				return;
			}
			if(item_select == 14){
				teleport_char(pPlayer,-473.0176,1746.8829,6.26);
				return;
			}
			if(item_select == 15){
				teleport_char(pPlayer,237.5457,-805.6555,13.7);
				return;
			}
			if(item_select == 16){
				teleport_char(pPlayer,-3.4734,270.6067,-2.9470);
				return;
			}
			if(item_select == 17){
				teleport_char(pPlayer,-1539.8414,163.2967,9.9000);
				return;
			}
			if(item_select == 18){
				xmc_teleportinfront();
				return;
			}			
		}
		if(last_selected[0] == 5){
			if(item_select == 4){
				do_toggle(chat_thingy);
				return;
			}
			if(item_select == 5){
				do_toggle(drive_free);
				if(drive_free){
					SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
					SWITCH_AMBIENT_PLANES(false);
				}
				else{
					SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
					SWITCH_AMBIENT_PLANES(true);
				}
				return;
			}
			if(item_select == 6){
				SHUTDOWN_AND_LAUNCH_NETWORK_GAME(2);
				return;
			}
			if(item_select == 7){
				SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
				return;
			}
			if(item_select == 8){
				print(GET_PLAYER_NAME(GET_HOST_ID()));
			}
			if(item_select == 9){
					
				
				print("Removed");
			}
		}
		if(last_selected[0] == 6){
			//
			return;
		}
	}
	if(menu_level == 2){
		if(last_selected[0] == 1){
			if(last_selected[1] == 2){
				if(item_select == 1){
					if(menu[item_select].value == 1){
						REQUEST_ANIMS("amb@park_taichi_a");
						while(!HAVE_ANIMS_LOADED("amb@park_taichi_a")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi01","amb@park_taichi_a",8.0,0,0);
						return;
					}
					if(menu[item_select].value == 2){
						REQUEST_ANIMS("amb@park_taichi_b");
						while(!HAVE_ANIMS_LOADED("amb@park_taichi_b")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi02","amb@park_taichi_b",8.0,0,0);
						return;
					}					
				}
				if(item_select == 2){
					if(menu[item_select].value == 1){
						REQUEST_ANIMS("amb@dance_maleidl_a");
						while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_a")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_maleidl_a",8.0,0,0);
						return;
					}
					if(menu[item_select].value == 2){
						REQUEST_ANIMS("amb@dance_maleidl_b");
						while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_b")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_maleidl_b",8.0,0,0);
						return;
					}
					if(menu[item_select].value == 3){
						REQUEST_ANIMS("amb@dance_maleidl_c");
						while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_c")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_maleidl_c",8.0,0,0);
						return;
					}
					if(menu[item_select].value == 4){
						REQUEST_ANIMS("amb@dance_maleidl_b");
						while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_b")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_maleidl_b",8.0,0,0);
						return;
					}
				}
				if(item_select == 3){
					if(menu[item_select].value == 1){
						REQUEST_ANIMS("amb@dance_femidl_a");
						while(!HAVE_ANIMS_LOADED("amb@dance_femidl_a")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_femidl_a",8.0,0,0);
						return;
					}
					if(menu[item_select].value == 2){
						REQUEST_ANIMS("amb@dance_femidl_b");
						while(!HAVE_ANIMS_LOADED("amb@dance_femidl_b")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_femidl_b",8.0,0,0);
						return;
					}
					if(menu[item_select].value == 3){
						REQUEST_ANIMS("amb@dance_femidl_c");
						while(!HAVE_ANIMS_LOADED("amb@dance_femidl_c")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_femidl_c",8.0,0,0);
						return;
					}					
				}
				if(item_select == 4){
					REQUEST_ANIMS("missstripclublo");
					while(!HAVE_ANIMS_LOADED("missstripclublo")) WAIT(0);
					TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"pole_dance_a","missstripclublo",8.0,0,0);
					return;
				}
				if(item_select == 5){
					SWITCH_PED_TO_RAGDOLL(pPlayer,20,30,false,false,false,false);
					SWITCH_PED_TO_ANIMATED(pPlayer,true);
					GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
					WAIT(30);
					SWITCH_PED_TO_ANIMATED(pPlayer,false);
					GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
					return;
				}
				if(item_select == 6){
					do_toggle(ragdoll);
					return;
				}
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(item_select == 1){
					if(menu[item_select].value == 1){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
						print("You have been given advanced weapons.");
					}
					else if(menu[item_select].value == 2){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MOLOTOV,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
						print("You have been given poor weapons.");						
					}
					else if(menu[item_select].value == 3){
						uint episode = GET_CURRENT_EPISODE();
						if(episode == 2){
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
							print("You have been given TBOGT weapons.");
							return;
						}
						print("You must be on The Ballad of Gay Tony to use this");
					}
					return;
				}
				else if(item_select == 3){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
					print("You have been given some grenades");				
				}
				else if(item_select == 4){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
					print("You have been given a Glock 17");		
				}
				else if(item_select == 5){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
					print("You have been given a Desert Eagle");		
				}
				else if(item_select == 6){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
					print("You have been given a Pump Shotgun");		
				}
				else if(item_select == 7){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
					print("You have been given a Tactical Shotgun");		
				}
				else if(item_select == 8){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
					print("You have been given a Micro Uzi");		
				}
				else if(item_select == 9){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
					print("You have been given an MP5");		
				}
				else if(item_select == 10){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
					print("You have been given an AK-47");		
				}
				else if(item_select == 11){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
					print("You have been given an AR-15");		
				}
				else if(item_select == 12){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
					print("You have been given an M40A1");		
				}
				else if(item_select == 13){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
					print("You have been given a Sniper Rifle");		
				}
				else if(item_select == 14){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
					print("You have been given an RPG");		
				}
				else if(item_select == 15){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
					print("You have been given a baseball bat");		
				}
				else if(item_select == 16){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
					print("You have been given a pool cue");			
				}
				return;
			}
		}
		if(last_selected[0] == 5){
			if(last_selected[1] == 1){
				if(item_select == 1){
					do_toggle(chat_thingy_use_color);
					return;
				}
				if(item_select == 2){
					s_r = 255;
					s_g = 0;
					s_b = 0;
					return;
				}
				if(item_select == 3){
					s_r = 0;
					s_g = 191;
					s_b = 255;
					return;
				}
				if(item_select == 4){
					s_r = 0;
					s_g = 255;
					s_b = 0;
					return;
				}
				if(item_select == 5){
					s_r = 255;
					s_g = 0;
					s_b = 255;
					return;
				}
			}
			if(last_selected[1] == 2){
				if(item_select == 1){
					int i = 0;
					for(i;i <= 5;i++){
						create_throwable_object(0x9976ECC4);
					}
				}
				if(item_select == 2){
					create_throwable_object(0x6066DF1D);
				}
				if(item_select == 3){ //cubes :D
					create_throwable_object(0x2718C626);
					create_throwable_object(0xDD28B247);
					create_throwable_object(0xCCEA11CA);
					create_throwable_object(0xBB1F6E71);
					create_throwable_object(0xA6E545FD);
					create_throwable_object(0x5C5030D4);
				}
				if(item_select == 4){
					int i = 0;
					for(i;i <= 5;i++){
						create_throwable_object(0x9D2A7EF8);
					}
				}
				if(item_select == 5){
					int i = 0;
					for(i;i <= 5;i++){
						create_throwable_object(0x501811B6);
					}
				}				
			}
			if(last_selected[1] == 3){
				if(item_select == 1){
					create_big_explosion(2247.4224,755.9057,5.853);
					WAIT(500);
					create_big_explosion(2231.6912,737.4642,5.853);
					WAIT(500);
					create_big_explosion(2214.0000,718.9000,5.83);
					WAIT(500);
					print("Target down!");				
					return;
				}
				if(item_select == 2){
					create_big_explosion(2621.6484,445.9162,5.35);
					print("Target down!");
					return;
				}
				if(item_select == 3){
					create_big_explosion(2268.2544,519.2332,5.4396);
					WAIT(500);
					create_big_explosion(2228.9453,526.2129,5.4401);
					WAIT(500);
					create_big_explosion(2221.8818,484.9935,5.4562);
					WAIT(500);
					create_big_explosion(2234.6369,456.6962,5.4562);
					print("Target down!");
				}
			}
		}
	}
	if(menu_level == 3){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){ //Online players
				if(last_selected[2] == 1){ //All players
					print("Removed");
				}
				else{
					uint index = (last_selected[2] - 2);
					if(item_select == 1){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(menu[item_select].value == 1){
								REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_DEAGLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_GRENADE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MP5,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M4,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BARETTA,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BASEBALLBAT,1,false);
							}
							else if(menu[item_select].value == 2){
								REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_PISTOL,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MOLOTOV,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MICRO_UZI,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_AK47,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SHOTGUN,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M40A1,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BASEBALLBAT,1,false);						
							}
							else if(menu[item_select].value == 3){
								uint episode = GET_CURRENT_EPISODE();
								if(episode == 2){
									REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
									WAIT(10);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_9,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_10,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_13,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_14,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_15,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_1,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_16,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BASEBALLBAT,1,false);
								}
								else{
									print("You must be on The Ballad of Gay Tony to use this option");
									return;
								}
							}
							GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_ARMOUR,1,false);
							ADD_ARMOUR_TO_CHAR(players[index].ped,99);
							print("Player is now armed & dangerous!");
							return;
						}
					}
					else if(item_select == 2){ 
						if(DOES_CHAR_EXIST(players[index].ped)){
							REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
							print("Player is now unarmed!");
							return;
						}
					}
					else if(item_select == 3){
						int tmp = players[index].id;
						do_toggle(players[tmp].juggernaut);
						return;
					}
					else if(item_select == 4){
						int tmp = players[index].id;
						//do_toggle(players[tmp].force);
						print("Removed");
						return;
					}
					else if(item_select == 5){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(menu[item_select].value == 1){
								float x,y,z;
								GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
								teleport_char(pPlayer,x,y,z);
								return;
							}
							if(menu[item_select].value == 2){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									Vehicle pveh;
									uint i;
									Ped tmp;
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									for(i = 0;i <= 2;i++){
										if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)){
											WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,pveh,i);
											return;
										}
									}
								}
							}
							if(menu[item_select].value == 3){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									float x,y,z;
									GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
									teleport_char(players[index].ped,x,y,z);
									return;
								}
								print("Player not in vehicle");
								return;
							}
							return;
						}
					}
					else if(item_select == 6){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								Vehicle pveh;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								ATTACH_PED_TO_CAR(pPlayer,pveh,0,0.00,0.00,1.5,0.00,0.00,1,1);
							}
							else print("Player needs to be in a vehicle");
						}
					}
					else if(item_select == 7){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								int pveh,nvid,tick;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("Error");
										return;
									}
									WAIT(0);
								}
								SET_CAR_CAN_BE_DAMAGED(pveh,true);
								SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
								SET_CAN_BURST_CAR_TYRES(pveh,true);
							}
							print("Whiskey Tango, this is Rubber Ducky comin' in hot!");
							float x,y,z;
							GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
							create_big_explosion(x,y,z);						
						}
					}
					else if(item_select == 8){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(GET_HOST_ID() != GET_PLAYER_ID()){
								if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
									float x,y,z;
									GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
									ADD_EXPLOSION(x,y,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
									ADD_EXPLOSION(x + 2.0,y,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
									ADD_EXPLOSION(x,y + 2.0,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
									ADD_EXPLOSION(x - 2.0,y,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
									ADD_EXPLOSION(x,y - 2.0,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
									print("Tazed nigga!");
								}
								else print("Player must be on foot");
							}
							else print("I don't wanna!");
						}
					}
					else if(item_select == 9){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								int pveh,nvid,tick;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("Error");
										return;
									}
									WAIT(0);
								}
								DELETE_CAR(&pveh);
								MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
							}
							else print("Player not in vehicle");
						}
					}
					else if(item_select == 10){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								int pveh,nvid,tick;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("Error");
										return;
									}
									WAIT(0);
								}
								APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
							}
							else print("Player not in vehicle");
						}
					}
					else if(item_select == 11){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								int pveh,nvid,tick;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("Error");
										return;
									}
									WAIT(0);
								}
								SET_CAR_CAN_BE_DAMAGED(pveh,true);
								SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
								SET_CAN_BURST_CAR_TYRES(pveh,true);
								BURST_CAR_TYRE(pveh,0);
								BURST_CAR_TYRE(pveh,1);
								BURST_CAR_TYRE(pveh,4);
								BURST_CAR_TYRE(pveh,5);
								SET_ENGINE_HEALTH(pveh,0.0);
							}
						}
						return;
					}
					else if(item_select == 12){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								int pveh,nvid,tick;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("Error");
										return;
									}
									WAIT(0);
								}
								REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
								SET_CAR_COORDINATES(pveh,-1079.8,-469.7,2.62);
								WAIT(500);
								DELETE_CAR(&pveh);
								MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
							}
							else print("Player not in vehicle");
						}						
					}
					else if(item_select == 13){
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(GET_PLAYER_ID() == GET_HOST_ID())
								NETWORK_KICK_PLAYER(players[index].id,true);
							else
								print("You are not host");
							return;
						}
					}
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					Vehicle pveh;
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(IS_VEHICLE_EXTRA_TURNED_ON(pveh,item_select))
							TURN_OFF_VEHICLE_EXTRA(pveh,item_select,true);
						else
							TURN_OFF_VEHICLE_EXTRA(pveh,item_select,false);
							
						reset_menu();
						return;
					}
					print("You must be in a vehicle");
				}
				if(last_selected[2] == 3){
					Vehicle pveh;
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(item_select == 1){
							uint color1,color2;
							GET_CAR_COLOURS(pveh,&color1,&color2);
							CHANGE_CAR_COLOUR(pveh,(menu[item_select].value - 1),color2);
							return;
						}
						if(item_select == 2){
							uint color1,color2;
							GET_CAR_COLOURS(pveh,&color1,&color2);
							CHANGE_CAR_COLOUR(pveh,color1,(menu[item_select].value - 1));
							return;
						}
						if(item_select == 3){
							uint color1,color2;
							GET_EXTRA_CAR_COLOURS(pveh,&color1,&color2);
							SET_EXTRA_CAR_COLOURS(pveh,(menu[item_select].value - 1),color2);
							return;
						}	
						if(item_select == 4){
							uint color1,color2;
							GET_EXTRA_CAR_COLOURS(pveh,&color1,&color2);
							SET_EXTRA_CAR_COLOURS(pveh,color1,(menu[item_select].value - 1));
							return;
						}						
					}
					print("You must be in a vehicle");
					return;
				}
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2 && GET_CURRENT_EPISODE() == 2){
					if(item_select == 1){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
						print("You have been given a .44 Pistol.");
						return;
					}
					if(item_select == 2){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
						print("You have been given an Explosive AA12.");
						return;
					}
					if(item_select == 3){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_11,AMMO_MAX,false);
						print("You have been given an AA12.");
						return;
					}
					if(item_select == 4){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_12,AMMO_MAX,false);
						print("You have been given a P-90.");
						return;
					}
					if(item_select == 5){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
						print("You have been given an Uzi.");
						return;
					}
					if(item_select == 6){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
						print("You have been given an M249.");
						return;
					}
					if(item_select == 7){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
						print("You have been given an Explosive Sniper.");
						return;
					}
					if(item_select == 8){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
						print("You have been given a Grenade Launcher.");
						return;
					}
					if(item_select == 9){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
						print("You have been given some Sticky Bombs.");
						return;
					}					
				}
			}
		}
	}
	if(menu_level == 4){
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					spawn_car(menu[item_select].value);
					return;
				}
			}
		}	
	}
}

void looped_functions(void){
	//player options
	SET_CHAR_INVINCIBLE(pPlayer,godmode);
	if(pprotection){
		uint pos[4];
		GET_POSITION_OF_ANALOGUE_STICKS(0,&pos[0],&pos[1],&pos[2],&pos[3]);
		if(pos[0] == 0 && pos[1] == 0)
			FREEZE_CHAR_POSITION(pPlayer,true);
		else
			FREEZE_CHAR_POSITION(pPlayer,false);
	}
		
	if(superrun){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_PRESSED(0,BUTTON_A)){
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,100.0,0.0,0.0,0.0,0.0,true,true,true,true);
			}
		}
	}
	
	if(superjump){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_PRESSED(0,BUTTON_X)){
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,0.0,50.0,0.0,0.0,0.0,true,true,true,true);
			}
		}	
	}
	
	if(forcefield){
		float x,y,z;
		GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
		ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,10.0,false,true,0.0);
	}
	
	if(ragdoll){
		if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_JUST_PRESSED(0,BUTTON_B)){
			if(!IS_PED_RAGDOLL(pPlayer)){
				SWITCH_PED_TO_RAGDOLL(pPlayer,20000,30000,false,false,false,false);
				SWITCH_PED_TO_ANIMATED(pPlayer,true);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
			}
			else{
				SWITCH_PED_TO_ANIMATED(pPlayer,false);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
			}
		}
	}
	
	//vehicles
	Vehicle pveh;
	if(vhelper){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			SET_CAR_CAN_BE_DAMAGED(pveh,false);
			SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
			SET_CAN_BURST_CAR_TYRES(pveh,false);
		}
	}
	if(carsonground){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			SET_CAR_ON_GROUND_PROPERLY(pveh);
		}
	}
	if(nfs){
		if(IS_CHAR_IN_ANY_CAR(pPlayer) && IS_BUTTON_PRESSED(0,BUTTON_R)){
			float speed;
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			GET_CAR_SPEED(pveh,&speed);
			SET_CAR_FORWARD_SPEED(pveh,(speed * 1.02));
		}
	}
	
	//weapons
	if(ammo){
		if(IS_CHAR_SHOOTING(pPlayer)){
			uint weapon,ammo;
			GET_CURRENT_CHAR_WEAPON(pPlayer,&weapon);
			if(weapon != WEAPON_GRENADE && weapon != WEAPON_MOLOTOV){
				GET_MAX_AMMO_IN_CLIP(pPlayer,weapon,&ammo);
				SET_AMMO_IN_CLIP(pPlayer,weapon,ammo);
			}
		}
	}
	//misc
	if(chat_thingy){
		int i;
		float pos_y = 0.875;
		for(i = 16;i >= 0;i--){
			if(i < 0) continue;
			if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
			if(!NETWORK_IS_PLAYER_TALKING(i)) continue;
			if(NETWORK_IS_PLAYER_MUTED_BY_ME(i)) continue;
			if(chat_thingy_use_color){
				GET_PLAYER_RGB_COLOUR(i,&r,&g,&b);
			}
			else{
				r = 255;
				g = 255;
				b = 255;
			}
			set_up_draw(3,0.3,0.3,r,g,b,255);
			draw_text("STRING",0.70,pos_y,GET_PLAYER_NAME(i));
			pos_y -= 0.03;			
		}
	}

	if(GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT("player_menuiv") != 0 && show_menu)
		menu_shutdown();
	
	//garage
	if(in_paint && IS_CHAR_IN_ANY_CAR(pPlayer)){
		if(menu[item_select].value != menu[item_select].extra_val){
			uint color1,color2,spec1,spec2;
			GET_CAR_COLOURS(pveh,&color1,&color2);
			GET_EXTRA_CAR_COLOURS(pveh,&spec1,&spec2);
			if(item_select == 1)
				CHANGE_CAR_COLOUR(pveh,(menu[item_select].value - 1),color2);
			if(item_select == 2)
				CHANGE_CAR_COLOUR(pveh,color1,(menu[item_select].value - 1));
			if(item_select == 3)
				SET_EXTRA_CAR_COLOURS(pveh,(menu[item_select].value - 1),spec2);				
			if(item_select == 4)
				SET_EXTRA_CAR_COLOURS(pveh,spec1,(menu[item_select].value - 1));

			menu[item_select].extra_val = menu[item_select].value;
		}
	}
	return;
}

void better_grenade_loop(void){
	if(grenade_active){
		if(!IS_PED_HOLDING_AN_OBJECT(pPlayer)){
			uint tick;
			float x,y,z;
			grenade_active = false;
			while(!HAS_OBJECT_COLLIDED_WITH_ANYTHING(tmp_object_loop)){
				tick++;
				if(tick > 1000) return;
				WAIT(0);
			}
			GET_OBJECT_COORDINATES(tmp_object_loop,&x,&y,&z);
			ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
			DELETE_OBJECT(&tmp_object_loop);
			MARK_OBJECT_AS_NO_LONGER_NEEDED(&tmp_object_loop);
		}
	}
	if(IS_PED_HOLDING_AN_OBJECT(pPlayer)){
		tmp_model = GET_MODEL_PED_IS_HOLDING(pPlayer);
		if(tmp_model == 0x501811B6 || tmp_model == 0x1B42315D){//object to be new grenade
			grenade_active = true;
			tmp_object_loop = GET_OBJECT_PED_IS_HOLDING(pPlayer);
		}
		else grenade_active = false;
	}
}

void do_online_player_loop(void){
	int i;
	bool reset_timer = false;
	uint ammo,weapon,armor;
	float x,y,z;
	Ped tmp;
	for(i = 0;i <= 16;i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)){
			players[i].juggernaut = false;
			players[i].force = false;
			continue;
		}
		GET_PLAYER_CHAR(i,&tmp);
		if(DOES_CHAR_EXIST(tmp)){
			if(players[i].juggernaut){
				GET_CHAR_ARMOUR(tmp,&armor);
				if(armor < 99){
					GIVE_WEAPON_TO_CHAR(tmp,WEAPON_ARMOUR,1,false);
					ADD_ARMOUR_TO_CHAR(tmp,99);
				}
			}

		}
	}
	return;
}