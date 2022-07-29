/*
 * LCD_Routines.c
 * Main.c should use LCD_updt_temps LCD_usr_inputs LCD_set_flags to set parameters in LCD_data
 * then call LCD_refresh()... see Custom_LCD_test() for basic test functions
 *
 *  "MX_LPTIM1_Init();" May fight with the LCD funciton
 *
 *  Created on: Jul 18, 2022
 *      Author: Joel M / Jesse F
 *
 */

#include "LCD_1in8.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_Routines.h"
#include <stdio.h>

//Variables
uint8_t PREV_STATE = 0;					//Previous state of state machine
uint8_t X_POS = LIVE_TMP_X+1;		//Current x-axis pixel for live temp plot
volatile LCD_DATA LCD_data;				//Interfaced with by main
char amb_tmp_BUFFER[]=	{' ',' ','0','.','6','9','\0'};
char plt_tmp_BUFFER[]=	{' ',' ','0','.','9','6','\0'};
char set_refl_temp_BUFFER[]=	{' ',' ','9','.','0','6','\0'};
char set_refl_time_BUFFER[]=	{' ',' ','1','.','0','6','\0'};
char set_preh_temp_BUFFER[]=	{' ',' ','9','.','0','6','\0'};
char set_preh_time_BUFFER[]=	{' ',' ','1','.','0','6','\0'};

/*
 *  Update measured temperatures
 */
void LCD_updt_temps(volatile float *cur_plt_tmp, volatile float *cur_amb_tmp){
	LCD_data.CUR_PLT_TMP= *cur_plt_tmp;
	LCD_data.CUR_AMB_TMP= *cur_amb_tmp;
}

/*
 *  Update configurable variables
 */
void LCD_usr_inputs(volatile float* set_preheat_tmp, volatile float* set_preheat_tim,
					volatile float* set_reflow_tmp, volatile float* set_reflow_tim) {

    LCD_data.SET_REFL_TMP = *set_reflow_tmp;
    LCD_data.SET_PRE_TMP = *set_preheat_tmp;
    LCD_data.PREHEAT_TIME = *set_preheat_tim;
    LCD_data.REFLOW_TIME = *set_reflow_tim;

}

/*
 * 	Update flags for system (turn left, turn right, sensor status ect. see ".h")
 */
void LCD_set_flags(uint16_t *flags){
	LCD_data.flags=*flags;
}

/*
 * Initialize LCD with a black screen, and LCD_data
 */
void LCD_init(void){
		//Power up LCD
		//HAL_GPIO_WritePin(DISP_DIS_GPIO_Port, DISP_DIS_Pin, 0);		//Power up LCD
		HAL_Delay(100);

		// Begin LCD Init
		DEV_Module_Init();
		LCD_1IN8_Init(SCAN_DIR_DFT);
		LCD_1IN8_Clear(BLACK);
		Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
		Paint_SetClearFuntion(LCD_1IN8_Clear);
		Paint_SetDisplayFuntion(LCD_1IN8_DrawPaint);

		LCD_data.CUR_AMB_TMP=255;
		LCD_data.CUR_PLT_TMP=255;
		LCD_data.SET_REFL_TMP=255;
		LCD_data.REFLOW_TIME=255;
		LCD_data.SET_PRE_TMP=255;
		LCD_data.REFLOW_TIME=255;
		LCD_data.STATE=0;
		LCD_data.flags=0;

		LCD_Set_State(0);
	return;
}

/*
 *  Format float as xxx.xx from x.xx/xx.xx/xxx.xx for display on LCD
 *  Returns 1 if successful 0 if failed to format
 */
uint8_t LCD_Format(char *string_ptr, float number){
	sprintf(string_ptr, "%.2f", number);
	char temp_buffer[]={' ',' ','x','.','x','x','\0'};
	uint8_t temp_pos = 3;
	uint8_t i;

	//Parse through elements
	for(i=0;i<(TEMP_RES+1);i++){

		//Find the decimal
		if(*string_ptr=='.'){

			//Next two digits are the ".xx"
			temp_buffer[4]=*(string_ptr+1);
			temp_buffer[5]=*(string_ptr+2);

			//Populate temp_buffer with correct stuff
			while(i>0){
				temp_pos--;
				i--;
				string_ptr--;
				temp_buffer[temp_pos]=*(string_ptr);
			}

			//push all temp_buffer data into the string, just finna hard code
			*(string_ptr)	=temp_buffer[0];
			*(string_ptr+1)	=temp_buffer[1];
			*(string_ptr+2)	=temp_buffer[2];
			*(string_ptr+3)	=temp_buffer[3];
			*(string_ptr+4)	=temp_buffer[4];
			*(string_ptr+5)	=temp_buffer[5];

			//Text string is formatted
			return 1;
		}

		//Check next element
		string_ptr++;
	}

return 0;
}

/*
 *  Updates LCD based on contents of LCD_Data struct
 *  NOTES:
 *  	- Using using black background and white foreground clears whatever previous test was on that line
 */
void LCD_Refresh(uint8_t cur_STATE){
	LCD_data.STATE=cur_STATE;

	//If the state machine changed reconfigure GUI
	if(PREV_STATE != LCD_data.STATE){
		LCD_Set_State(LCD_data.STATE);
		PREV_STATE=LCD_data.STATE;
	}

	//	Main state machine for LCD refresh
	switch(LCD_data.STATE){

	//Initial boot up
	case 0:
		if((LCD_data.flags & 0x80) ==0x80 )
			Paint_DrawString_EN(26, 104, "OKAY", &Font8, BLACK, WHITE);
		if((LCD_data.flags & 0x40) ==0x40 )
			Paint_DrawString_EN(46, 112, "OKAY", &Font8, BLACK, WHITE);
		if((LCD_data.flags & 0x20) ==0x20 )
			Paint_DrawString_EN(46, 120, "OKAY", &Font8, BLACK, WHITE);
		break;

	//Configure Hot plate
	case 1:
		LCD_Format(set_preh_temp_BUFFER,LCD_data.SET_PRE_TMP);
		LCD_Format(set_preh_time_BUFFER,LCD_data.PREHEAT_TIME);
		LCD_Format(set_refl_temp_BUFFER,LCD_data.SET_REFL_TMP);
		LCD_Format(set_refl_time_BUFFER,LCD_data.REFLOW_TIME);
		Paint_DrawString_EN(71, 24, set_preh_temp_BUFFER, &Font12, BLACK, WHITE);
		Paint_DrawString_EN(71, 40, set_preh_time_BUFFER, &Font12, BLACK, WHITE);
		Paint_DrawString_EN(71, 56, set_refl_temp_BUFFER, &Font12, BLACK, WHITE);
		Paint_DrawString_EN(71, 72, set_refl_time_BUFFER, &Font12, BLACK, WHITE);
		break;

	//Hot Plate Heating Graph
	case 2:
		LCD_Format(plt_tmp_BUFFER,LCD_data.CUR_PLT_TMP);
		Paint_DrawString_EN(1, 120,  plt_tmp_BUFFER, &Font8, BLACK, WHITE);
		Paint_DrawPoint(X_POS,(LIVE_TMP_Y-(LCD_data.CUR_PLT_TMP/2)), RED, DOT_PIXEL_1X1, DOT_FILL_AROUND);	//Add point to graph
		X_POS++;
		if(X_POS>160){					//Increment xpos of live graph point
			LCD_Clear_Plot();
			X_POS=LIVE_TMP_X+1;
		}

		break;

	//Hot Plate Heating Values (same data as case 2 just no graph)
	case 3:
		LCD_Format(amb_tmp_BUFFER,LCD_data.CUR_AMB_TMP);
		LCD_Format(plt_tmp_BUFFER,LCD_data.CUR_PLT_TMP);
		Paint_DrawString_EN(98, 88,  plt_tmp_BUFFER, &Font12, BLACK, WHITE);
		Paint_DrawString_EN(98, 104,  amb_tmp_BUFFER, &Font12, BLACK, WHITE);
		break;

	//Catch of invalid state
	default:
		Paint_DrawString_EN(1, 1, "DEFAULT", &Font8, BLACK, WHITE);
		break;
	}

}

/*
 * Clears the graph area for state 2
 */
void LCD_Clear_Plot(){
	Paint_ClearWindows(LIVE_TMP_X, 0, LCD_1IN8_WIDTH, LIVE_TMP_Y-1, BLACK);	//Clear graph area

	//grid lines for temp
	Paint_DrawLine(LIVE_TMP_X+1, 104, LCD_1IN8_WIDTH, 104, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(LIVE_TMP_X+1,  88, LCD_1IN8_WIDTH,  88, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(LIVE_TMP_X+1,  72, LCD_1IN8_WIDTH,  72, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(LIVE_TMP_X+1,  56, LCD_1IN8_WIDTH,  56, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(LIVE_TMP_X+1,  40, LCD_1IN8_WIDTH,  40, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(LIVE_TMP_X+1,  24, LCD_1IN8_WIDTH,  24, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	//Paint_DrawLine(LIVE_TMP_X+1,   8, LCD_1IN8_WIDTH,   8, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

	/*Might be better to store datapoints somewhere and just clear those instead of whole window*/
}

/*
 *  Some new states require the LCD to be cleared before new text can be added
 *  This function clears the LCD and configures it for the NEW STATE
 */
void LCD_Set_State(uint8_t test_STATE){
	PREV_STATE=test_STATE;

	//Main Switch Case
	switch(test_STATE){
		//Initial boot up
		case 0:
			LCD_1IN8_Clear(BLACK);
			Paint_DrawString_EN(120,1, "STATE 0", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 32, "THE HOT POTATO", &Font16, BLACK, WHITE);
			Paint_DrawString_EN(24, 56, "SMD REFLOW", &Font16, BLACK, WHITE);
			Paint_DrawString_EN(1, 96, "Initialization:", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 104, "IMU: ...", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 112, "TEMP #1: ...", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 120, "TEMP #2: ...", &Font8, BLACK, WHITE);
			break;

		//Configure Hot plate
		case 1:
			LCD_1IN8_Clear(BLACK);
			Paint_DrawString_EN(120,1, "STATE 1", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 24, "Set P_Temp:       `C", &Font12, BLACK, WHITE);
			Paint_DrawString_EN(1, 40, "Set P_Tim:        min", &Font12, BLACK, WHITE);
			Paint_DrawString_EN(1, 56, "Set R_Temp:       `C", &Font12, BLACK, WHITE);
			Paint_DrawString_EN(1, 72, "Set R_Tim:        min", &Font12, BLACK, WHITE);
			break;

		//Hot Plate Heating
		case 2:
			LCD_1IN8_Clear(BLACK);
			Paint_DrawString_EN(120, 1, "STATE 2", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 1, "Temp", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 9, "`C", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(80, 120, "Time", &Font8, BLACK, WHITE);

			//main xy axis
			Paint_DrawLine(LIVE_TMP_X, 16, LIVE_TMP_X, LIVE_TMP_Y, YELLOW, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
			Paint_DrawLine(0, LIVE_TMP_Y, LCD_1IN8_WIDTH, LIVE_TMP_Y, YELLOW, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

			//Temp markings
			Paint_DrawString_EN(1,104-5, " 32", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 88-5, " 64", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 72-5, " 96", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 56-5, "128", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 40-5, "160", &Font8, BLACK, WHITE);
			Paint_DrawString_EN(1, 24-5, "192", &Font8, BLACK, WHITE);
			//Paint_DrawString_EN(1,  8, "224", &Font8, BLACK, WHITE);

			//grid lines for temp
			Paint_DrawLine(LIVE_TMP_X+1, 104, 160, 104, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
			Paint_DrawLine(LIVE_TMP_X+1,  88, 160,  88, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
			Paint_DrawLine(LIVE_TMP_X+1,  72, 160,  72, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
			Paint_DrawLine(LIVE_TMP_X+1,  56, 160,  56, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
			Paint_DrawLine(LIVE_TMP_X+1,  40, 160,  40, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
			Paint_DrawLine(LIVE_TMP_X+1,  24, 160,  24, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
			//Paint_DrawLine(LIVE_TMP_X,   8, 160,   8, GRAY, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

			X_POS = LIVE_TMP_X+1;			//reset temp graphing position;
			break;

		//Another Temp Display
		case 3:
			LCD_1IN8_Clear(BLACK);
			Paint_DrawString_EN(120, 1, "STATE 3", &Font8, BLACK, WHITE);
			LCD_Format(set_refl_temp_BUFFER,LCD_data.SET_REFL_TMP);
			LCD_Format(plt_tmp_BUFFER,LCD_data.CUR_PLT_TMP);
			LCD_Format(amb_tmp_BUFFER,LCD_data.CUR_AMB_TMP);
			Paint_DrawString_EN(24, 8,  "Sensor Readings", &Font12, BLACK, WHITE);
			Paint_DrawString_EN(1, 72,  "Plate Target:       `C", &Font12, BLACK, WHITE);
			Paint_DrawString_EN(98, 72,  set_refl_temp_BUFFER, &Font12, BLACK, WHITE);
			Paint_DrawString_EN(1, 88,  "Plate Live:         `C", &Font12, BLACK, WHITE);
			Paint_DrawString_EN(98, 88,  plt_tmp_BUFFER, &Font12, BLACK, WHITE);
			Paint_DrawString_EN(1, 104, "Ambient Live:       `C", &Font12, BLACK, WHITE);
			Paint_DrawString_EN(98, 104,  amb_tmp_BUFFER, &Font12, BLACK, WHITE);
			break;

		//Catch of invalid state
		default:
			LCD_1IN8_Clear(BLACK);
			Paint_DrawString_EN(1, 48, "**State Machine Error**", &Font12, BLACK, WHITE);
			break;
	}

return;
}

/*
 *  Test Function that brings LCD through its various states
 */
void Custom_LCD_test(){

	//Variables we'll use
	uint16_t my_flags;				//system status and rotary encoder changes
	float set_hotplate_temp=69.69;	//hot plate temperature set by user
	float set_hotplate_soak=96.96;	//hot plate soak time set by user
	float live_ambient=11.012;		//live ambient temperature reading
	float live_plate=10.40;			//live hotplate temperature

	//Initialize LCD
	LCD_init();

	//Display Boot screen STATE 0
	LCD_Refresh(0);

	//initialize sensors and update flags STATE 0
	my_flags=(IMU_STAT);
	LCD_set_flags(&my_flags);
	LCD_Refresh(0);
	HAL_Delay(1000);

	my_flags=(IMU_STAT|TMP75_STAT);
	LCD_set_flags(&my_flags);
	LCD_Refresh(0);
	HAL_Delay(1000);

	my_flags=(IMU_STAT|TMP75_STAT|IR_STAT);
	LCD_set_flags(&my_flags);
	LCD_Refresh(0);
	HAL_Delay(1000);

	//Set hotplate temp and soak time STATE 1
	LCD_Refresh(1);
//	LCD_usr_inputs(&set_hotplate_temp, &set_hotplate_soak);
	LCD_Refresh(1);
	HAL_Delay(1000);

	//Display live temperature reading graph STATE 2
	LCD_Refresh(2);
	for(int i=0;i<200;i++){
		live_plate=live_plate+1;
		LCD_updt_temps(&live_plate, &live_ambient);
		LCD_Refresh(2);
	}

	//Display live temperature readings just as text (no graph) STATE 3
	LCD_Refresh(3);
	live_plate=20.32;
	for(int i=0;i<100;i++){
		live_plate=live_plate+1;
		live_ambient=live_ambient+0.54;
		LCD_updt_temps(&live_plate, &live_ambient);
		LCD_Refresh(3);
		HAL_Delay(250);
	}


}
