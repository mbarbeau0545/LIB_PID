/**
 * @file        Lib_Pid.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      sde
 * @date        17/01/2025
 * @version     1.0
 */
  
#ifndef LIB_PID_H_INCLUDED
#define LIB_PID_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define LIBPID_MAX_USER_REGISTRATION ((t_uint8) 14)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//

    /* CAUTION : Automatic generated code section for Enum: Start */
    typedef enum
    {
        LIBPID_FORMAT_RESULT_F32, /**< */
        
        LIBPID_FORMAT_RESULT_NB,
    } t_eLIBPID_FormatResult;

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------STRUCT TYPES---------------------------//

    typedef struct 
    {
        t_float32   Kp_f32;       //---- Proportional gain ----//
        t_float32   Ki_f32;       //---- Integral Gain ----//
        t_float32   Kd_f32;       //---- Derivative Gain ----//
        t_float32   outMin_f32;   //---- Minimum value computed by library ----//
        t_float32   outMax_f32;   //---- Maximumx value computed by library ----//
                
    } t_sLIBPID_ParamCfg;

    typedef struct
    {
        t_float32 coeffA0_f32;          /**< The derived gain, coeffA0_f32 = Kp_f32 + Ki_f32 + Kd_f32 . */
        t_float32 coeffA1_f32;          /**< The derived gain, coeffA1_f32 = -Kp_f32 - 2Kd_f32. */
        t_float32 coeffA2_f32;          /**< The derived gain, coeffA2_f32 = Kd_f32 . */
        t_float32 state_af32[3];        /**< The state_af32 array of length 3. */
        t_sLIBPID_ParamCfg prmCfg_s;    /**< Store the pid configuration */
        t_bool isInit_b;                /**< to know if the Pid has been initialized */
    } t_sLIBPID_PidInfo; 


    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************



    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /**
    *
    *	@brief      Configure and initialize PID.
    *   @example    For dutycycle, min = -1000 and max = 1000,
    *               try Kp = 1.0 and Ki,Kd = 0
    *
    *	@param[in]  f_PidInfo_ps          : Pointor to the structure that will contain the info
    *	@param[in]  f_ParamCfg_s          : Parameter for the pid equation
    *
    *  @return @ref t_eReturnCode
    */
    t_eReturnCode LIBPID_Init(     t_sLIBPID_PidInfo * f_PidInfo_ps,
                                    t_sLIBPID_ParamCfg f_ParamCfg_s);
    /**
    *
    *	@brief      Compute PID.
    *   @note       Compute the new value depeding on f_setPoint_f32,
    *               f_feedbackVal_f32 and previous error, THEY HAVE TO
    *               BE THE SAME UNIT !!!
    *               
    *
    *	@param[in]  f_PidInfo_ps          : Pointor to the structure that contain the info
    *	@param[in]  f_setPoint_f32        : set Point to reach
    *	@param[in]  f_feedbackVal_f32     : feedback value of the system
    *	@param[out] f_ValueComputed_pf32     : Storage for value computed
    *
    *  @return @ref t_eReturnCode
    */
    t_eReturnCode LIBPID_Compute(   t_sLIBPID_PidInfo * f_PidHandle_ps,
                                    t_float32 f_setPoint_f32,
                                    t_float32 f_feedbackVal_f32,
                                    t_float32 * f_ValueComputed_pf32);
    /**
    *
    *	@brief      Reset PID.
    *   @note       
    *               
    *
    *	@param[in]  f_PidInfo_ps          : Pointor to the structure that contain the info
    *
    *  @return @ref t_eReturnCode
    */
    t_eReturnCode LIBPID_Reset(t_sLIBPID_PidInfo * f_PidInfo_ps);  
    /**
    *
    *	@brief      Reset PID.
    *   @note       
    *               
    *
    *	@param[in]  f_PidInfo_ps          : Pointor to the structure that will contain the info
    *	@param[in]  f_NewParam_s          : Parameter for the pid equation
    *
    *  @return @ref t_eReturnCode
    */
    t_eReturnCode LIBPID_UpdateParam(t_sLIBPID_PidInfo * f_PidInfo_ps,
                                     t_sLIBPID_ParamCfg  f_NewParam_s);    



#endif // LIBPID_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

/**
 *	@brief
*	@note   
*
*
*	@param[in] 
*	@param[in]
*	 
*
*
*/
