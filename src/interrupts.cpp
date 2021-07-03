//#include <diskio.h>
#include <stm32f10x.h>
//#include <stm32f10x_tim.h>
#include <stm32f10x_usart.h>
#include <task/variables.h>

extern "C" {

void NMI_Handler(void) {}

void HardFault_Handler(void) {
    while (1) {}
}

void MemManage_Handler(void) {
    while (1) {}
}

void BusFault_Handler(void) {
    while (1) {}
}

void UsageFault_Handler(void) {
    while (1) {}
}

void DebugMon_Handler(void) {}
void WWDG_IRQHandler(void) {}
void PVD_IRQHandler(void) {}
void TAMPER_IRQHandler(void) {}
void RTC_IRQHandler(void) {}
void FLASH_IRQHandler(void) {}
void RCC_IRQHandler(void) {}
void EXTI0_IRQHandler(void) {}
void EXTI1_IRQHandler(void) {}
void EXTI2_IRQHandler(void) {}
void EXTI3_IRQHandler(void) {}
void EXTI4_IRQHandler(void) {}
void EXTI9_5_IRQHandler(void) {}
void EXTI15_10_IRQHandler(void) {}
void DMA1_Channel1_IRQHandler(void) {}
void DMA1_Channel2_IRQHandler(void) {}
void DMA1_Channel3_IRQHandler(void) {}
void DMA1_Channel4_IRQHandler(void) {}
void DMA1_Channel5_IRQHandler(void) {}
void DMA1_Channel6_IRQHandler(void) {}
void DMA1_Channel7_IRQHandler(void) {}
void ADC1_2_IRQHandler(void) {}
void USB_HP_CAN1_TX_IRQHandler(void) {}
void USB_LP_CAN1_RX0_IRQHandler(void) {}
void CAN1_RX1_IRQHandler(void) {}
void CAN1_SCE_IRQHandler(void) {}
void TIM1_BRK_IRQHandler(void) {}
void TIM1_UP_IRQHandler(void) {}
void TIM1_TRG_COM_IRQHandler(void) {}
void TIM1_CC_IRQHandler(void) {}

void TIM2_IRQHandler(void) {
//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//        disk_timerproc();
//    }
}

void TIM3_IRQHandler(void) {}
void TIM4_IRQHandler(void) {}
void I2C1_EV_IRQHandler(void) {}
void I2C1_ER_IRQHandler(void) {}
void I2C2_EV_IRQHandler(void) {}
void I2C2_ER_IRQHandler(void) {}
void SPI1_IRQHandler(void) {}
void SPI2_IRQHandler(void) {}
void USART1_IRQHandler(void) {}

void USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        xQueueSendFromISR(uartQueue, (void *) &USART2->DR, NULL);
    }
}

void USART3_IRQHandler(void) {}
void RTCAlarm_IRQHandler(void) {}

}