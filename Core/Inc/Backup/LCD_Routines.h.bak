
#include "LCD_1in8.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "main.h"

//Defines
#define TEMP_RES 5		//maximum resolution of display temperature, don't change me
#define LIVE_TMP_X 24	//x-axis border for live temp plot
#define LIVE_TMP_Y 120	//y-axis border for live temp plot

//Location of flag bits
#define IMU_STAT 0x80
#define TMP75_STAT 0x40
#define IR_STAT 0x20

/* @brief Setup gui for new state
 * @param new state of state machine
 */
void LCD_Set_State(uint8_t test_STATE);

/* @brief Initializes LCD for control
 * @param Void
 */
void LCD_init(void);

/* @brief Refresh LCD based on current state of system
 * @param cur_STATE current state of LCD for refreshing
 */
void LCD_Refresh(uint8_t cur_STATE);

/* @brief Formats a string of characters in the form xxx.xx'C
 * @param string_ptr pointer to the string to be formatted
 * @param number float that is to be formatted
 */
uint8_t LCD_Format(char *string_ptr, float number);

/* @brief Updates the measured temperatures in LCD_DATA struct
 * @param cur_plt_tmp pointer to float of measured plate temperature
 * @param cur_amb_tmp pointer to float of measured ambient temperature
 */
void LCD_updt_temps(float *cur_plt_tmp, float *cur_amb_tmp);

/* @brief Updates the measured temperatures in LCD_DATA struct
 * @param flags, pointer to 8bits of flags indicating desired changes
 */
void LCD_set_flags(uint16_t *flags);

/* @brief updates user input variables, set plate time, and set soak time
 * @param set_plt_tmp pointer to float of set plate temperature
 * @param set_soak_tim pointer to float of set ambient temperature
 */
void LCD_usr_inputs(float *set_plt_tmp, float *set_soak_tim);

/* @brief clears the graph area for the live temperature plot
 */
void LCD_Clear_Plot(void);

/*@brief test function that runs the LCD through all of its states
 */
void Custom_LCD_test(void);

/* @brief data structure to interface with the LCD
 */
typedef struct {
    volatile uint16_t flags;				// - IMU STAT - TMP75 STAT - IR STAT - x -    - x - LEFT - RIGHT - BUTTON -
    volatile float SET_PLT_TMP;			//Hot plate set temperature
    volatile float CUR_PLT_TMP;			//Hot plate measured temperature
    volatile float CUR_AMB_TMP;			//Current ambient temperature
    volatile uint8_t SOAK_TIME;			//Hot plate soak time set
    volatile uint8_t STATE;				//Current Hot plate soak time
} LCD_DATA;
extern volatile LCD_DATA LCD_data;
