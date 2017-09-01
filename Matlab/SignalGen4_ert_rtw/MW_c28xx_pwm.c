#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "F2806x_GlobalPrototypes.h"
#include "rtwtypes.h"
#include "SignalGen4.h"
#include "SignalGen4_private.h"

void config_ePWM_GPIO (void)
{
  EALLOW;

  /*-- Configure pin assignments for ePWM7 --*/
  GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1; /* Configure GPIOGPIO40 as EPWM7A*/
  GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1; /* Configure GPIOGPIO41 as EPWM7B*/

  /*-- Configure pin assignments for ePWM8 --*/
  GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1; /* Configure GPIOGPIO42 as EPWM8A*/
  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 1; /* Configure GPIOGPIO43 as EPWM8B*/

  /*--- Configure pin assignments for TZn ---*/
  EDIS;
}
