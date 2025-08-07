/**
 * @file        
 * @brief       LIB PID CONTROL MODULE.
 * @note        TemplateDetailsDescription.!!!WARNING!!! THE ONLY FORMAT POSSIBLE IS F32 !!!WARNING!!!.\n
 *
 * @author      sde
 * @date        17/01/2025
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./LIBPID.h"
#include <string.h>
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************

/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//

/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
    

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************

//********************************************************************************
//                      Local functions - Prototypes
//*******************************************************************************
/**
*
*	@brief      Reset PID.
*   @note       User need to transmit user id of his PID instance. 
*               
*
*	@param[in]  f_userId_u8              : Storage for user ID
*
*   @return ///
*/
static t_eReturnCode s_LIBPID_Reset_f32(t_sLIBPID_PidInfo * f_PidInfo_ps);
/**
*
*	@brief      Compute Pid with float32 computation. 
*               
*
*	@param[in]  f_userId_u8              : Storage for user ID
*
*   @return ///
*/
static t_eReturnCode s_LIBPID_Compute_f32(  t_sLIBPID_PidInfo * f_PidInfo_ps,
                                            t_float32 f_currentError_f32,
                                            t_float32 * f_ValueComputed_pf32);
//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//**********************
// LIBPID_Init
//**********************
t_eReturnCode LIBPID_Init(     t_sLIBPID_PidInfo * f_PidInfo_ps,
                                t_sLIBPID_ParamCfg f_ParamCfg_s)
{
    t_eReturnCode Ret_e;
    t_float32 coeffA0_f32;
    t_float32 coeffA1_f32;
    t_float32 coeffA2_f32;

    if(f_PidInfo_ps == (t_sLIBPID_PidInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        Ret_e = RC_OK;
        /**< The derived gain, coeffA0_f32 = Kp_f32 + Ki_f32 + Kd_f32 . */
        coeffA0_f32 = (t_float32)(f_ParamCfg_s.Kd_f32 + f_ParamCfg_s.Ki_f32 + f_ParamCfg_s.Kp_f32);
        /**< The derived gain, coeffA1_f32 = -Kp_f32 - 2Kd_f32. */
        coeffA1_f32 = (t_float32)((t_float32)(-2) * f_ParamCfg_s.Kd_f32 - f_ParamCfg_s.Kp_f32); 
        /**< The derived gain, coeffA2_f32 = Kd_f32 . */
        coeffA2_f32 = (t_float32)(f_ParamCfg_s.Kd_f32);


        f_PidInfo_ps->coeffA0_f32         = (t_float32)(coeffA0_f32);
        f_PidInfo_ps->coeffA1_f32         = (t_float32)(coeffA1_f32);
        f_PidInfo_ps->coeffA2_f32         = (t_float32)(coeffA2_f32);
        f_PidInfo_ps->prmCfg_s.Kd_f32     = (t_float32)f_ParamCfg_s.Kd_f32;
        f_PidInfo_ps->prmCfg_s.Ki_f32     = (t_float32)f_ParamCfg_s.Ki_f32;
        f_PidInfo_ps->prmCfg_s.Kp_f32     = (t_float32)f_ParamCfg_s.Kp_f32;
        f_PidInfo_ps->prmCfg_s.outMax_f32 = (t_float32)f_ParamCfg_s.outMax_f32;
        f_PidInfo_ps->prmCfg_s.outMin_f32 = (t_float32)f_ParamCfg_s.outMin_f32;
        f_PidInfo_ps->isInit_b            = (t_bool)TRUE;
    }

    return Ret_e;
}

//**********************
// LIBPID_Compute
//**********************
t_eReturnCode LIBPID_Compute(   t_sLIBPID_PidInfo * f_PidInfo_ps,
                                t_float32 f_setPoint_f32,
                                t_float32 f_feedbackVal_f32,
                                t_float32 * f_ValueComputed_pf32)

{
    t_eReturnCode Ret_e;
    t_float32 BufferValueComputed_f32;
    t_float32 currError_f32;

    if((f_PidInfo_ps == (t_sLIBPID_PidInfo *) NULL)
    || (f_ValueComputed_pf32 == (t_float32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;   
    }
    else if (f_PidInfo_ps->isInit_b == (t_bool)FALSE)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    else
    {
        currError_f32 = (t_float32)(f_setPoint_f32 - f_feedbackVal_f32);
        Ret_e = s_LIBPID_Compute_f32(   f_PidInfo_ps,
                                        currError_f32,
                                        &BufferValueComputed_f32);

        if(Ret_e == RC_OK)
        {
            if(BufferValueComputed_f32 > f_PidInfo_ps->prmCfg_s.outMax_f32)
            {
                *f_ValueComputed_pf32 = f_PidInfo_ps->prmCfg_s.outMax_f32;
            }
            else if(BufferValueComputed_f32 < f_PidInfo_ps->prmCfg_s.outMin_f32)
            {
                *f_ValueComputed_pf32 = f_PidInfo_ps->prmCfg_s.outMin_f32;
            }
            else 
            {
                *f_ValueComputed_pf32 = (t_float32) BufferValueComputed_f32;
            }
        }
    }

    return Ret_e;
}

//**********************
// LIBPID_Reset
//**********************
t_eReturnCode LIBPID_Reset(t_sLIBPID_PidInfo * f_PidInfo_ps)
{
    t_eReturnCode Ret_e;

    if(f_PidInfo_ps == (t_sLIBPID_PidInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_PidInfo_ps->isInit_b == (t_bool)FALSE)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    else 
    {
        //--- for now just the float 32 computation ----//
        Ret_e = s_LIBPID_Reset_f32(f_PidInfo_ps);
    }
    
    return Ret_e;
}

//**********************
// LIBPID_UpdateParam
//**********************
t_eReturnCode LIBPID_UpdateParam(t_sLIBPID_PidInfo * f_PidInfo_ps,
                                     t_sLIBPID_ParamCfg  f_NewParam_s)
{
    t_eReturnCode Ret_e;

    if(f_PidInfo_ps == (t_sLIBPID_PidInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_PidInfo_ps->isInit_b == (t_bool)FALSE)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    else 
    {
        Ret_e = RC_OK;
        f_PidInfo_ps->prmCfg_s.Kd_f32     = (t_float32)f_NewParam_s.Kd_f32;
        f_PidInfo_ps->prmCfg_s.Ki_f32     = (t_float32)f_NewParam_s.Ki_f32;
        f_PidInfo_ps->prmCfg_s.Kp_f32     = (t_float32)f_NewParam_s.Kp_f32;
        f_PidInfo_ps->prmCfg_s.outMax_f32 = (t_float32)f_NewParam_s.outMax_f32;
        f_PidInfo_ps->prmCfg_s.outMin_f32 = (t_float32)f_NewParam_s.outMin_f32;
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
//**********************
// s_LIBPID_Reset_f32
//**********************
static t_eReturnCode s_LIBPID_Reset_f32(t_sLIBPID_PidInfo * f_PidInfo_ps)
{
    t_eReturnCode Ret_e;

    if(f_PidInfo_ps == (t_sLIBPID_PidInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        Ret_e = RC_OK;
        /* Reset state to zero, The size will be always 3 samples */
        memset(f_PidInfo_ps->state_af32, 0, 3U * sizeof(t_float32));
    }

    return Ret_e;
}


//**********************
// s_LIBPID_Compute_f32
//**********************
static t_eReturnCode s_LIBPID_Compute_f32(  t_sLIBPID_PidInfo * f_PidInfo_ps,
                                            t_float32 f_currentError_f32,
                                            t_float32 * f_ValueComputed_pf32)
{
    t_eReturnCode Ret_e;
    t_float32 computeVal_f32;

    if((f_PidInfo_ps == (t_sLIBPID_PidInfo *) NULL)
    || (f_ValueComputed_pf32 == (t_float32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;   
    }
    else if (f_PidInfo_ps->isInit_b == (t_bool)FALSE)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    else
    {
        Ret_e = RC_OK;

        /* y[n] = y[n-1] + coeffA0_f32 * x[n] + coeffA1_f32 * x[n-1] + coeffA2_f32 * x[n-2]  */
        computeVal_f32 = (t_float32)(f_PidInfo_ps->state_af32[2]
                                    + (t_float32)(f_PidInfo_ps->coeffA0_f32 * f_currentError_f32)
                                    + (t_float32)(f_PidInfo_ps->coeffA1_f32 * f_PidInfo_ps->state_af32[0])
                                    + (t_float32)(f_PidInfo_ps->coeffA2_f32 * f_PidInfo_ps->state_af32[1]));

        /* Update state */
        f_PidInfo_ps->state_af32[1] = f_PidInfo_ps->state_af32[0]; 
        f_PidInfo_ps->state_af32[0] = f_currentError_f32; 
        f_PidInfo_ps->state_af32[2] = computeVal_f32; // y[n] 
        *f_ValueComputed_pf32 = computeVal_f32;
    }

    return Ret_e;

}
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
