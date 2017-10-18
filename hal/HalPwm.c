#include "HalPwm.h"
#include "stm32f10x_tim.h"

static void ledPwmInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // ����������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure); 

    
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           // ����������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period=10000;   //1s
    TIM_TimeBaseStructure.TIM_Prescaler=7199; //720��Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision=0;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

      
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;//PWM1ģʽ1
    TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;//�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 2500; //����ռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //����Ƚϼ��Ը�
    TIM_OC3Init(TIM4, & TIM_OCInitStructure);//��ʼ��TIM4��CH3ͨ��
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ��TIM4��CH3ͨ��CCR3�ϵ�Ԥװ�ؼĴ���
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ʹ��TIM4��CH3ͨ��ARR3�ϵ�Ԥװ�ؼĴ���
    TIM_Cmd(TIM4,ENABLE);//ʹ�ܶ�ʱ��4
#if 0
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
    /* PWM�źŵ�ƽ����ֵ */  
    /*PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz*/  
    /* Time base configuration */           
    TIM_TimeBaseStructure.TIM_Period = 100 - 1;  
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;                                    //����Ԥ��Ƶ��Ԥ��Ƶ=2����Ϊ72/3=24MHz  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                                //����ʱ�ӷ�Ƶϵ��������Ƶ  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //���ϼ������ģʽ  
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
    TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);
    /* PWM1 Mode configuration: Channel3 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //����ΪPWMģʽ1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
    TIM_OCInitStructure.TIM_Pulse = 50;                                       //��������ֵ�������������������ֵʱ����ƽ��������  
    TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_Low;                    //����ʱ������ֵС��CCR1ʱΪ�ߵ�ƽ  
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);    
    TIM_ARRPreloadConfig(TIM4,ENABLE);   
    TIM_Cmd(TIM4, ENABLE); 
    TIM_CtrlPWMOutputs(TIM4, ENABLE);
#endif
}

void HalPwmPluseSet(uint8_t pwmNo, uint8_t chn, uint16_t pluse)
{
    if(pwmNo == HAL_PWM_NUM_1)
    {
        switch(chn)
        {
            case 1:
                TIM_SetCompare1(TIM3, pluse);
                break;
            case 2:
                TIM_SetCompare2(TIM3, pluse);
                break;
            case 3:
                TIM_SetCompare3(TIM3, pluse);
                break;
            case 4:
                TIM_SetCompare4(TIM3, pluse);
                break;
            default:
                break;
        }
    }
}

void HalPwmConfig(uint8_t pwmNo, uint16_t defPluse)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  

    if(pwmNo == HAL_PWM_NUM_1)
    {
        /* PWM�źŵ�ƽ����ֵ */  
        /*PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz*/  
        /* Time base configuration */           
        //TIM_DeInit(TIM3);
        TIM_TimeBaseStructure.TIM_Period = 100 - 1;  
        TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;                                    //����Ԥ��Ƶ��Ԥ��Ƶ=2����Ϊ72/3=24MHz  
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                                //����ʱ�ӷ�Ƶϵ��������Ƶ  
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //���ϼ������ģʽ  
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
        TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
        TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
        
        /* PWM1 Mode configuration: Channel1 */  
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //����ΪPWMģʽ1  
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
        TIM_OCInitStructure.TIM_Pulse = defPluse;                                       //��������ֵ�������������������ֵʱ����ƽ��������  
        TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_Low;                    //����ʱ������ֵС��CCR1ʱΪ�ߵ�ƽ  
        TIM_OC1Init(TIM3, &TIM_OCInitStructure);                                    //ʹ��ͨ��1      
        //TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  
        
        /* PWM1 Mode configuration: Channel2 */  
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
        TIM_OCInitStructure.TIM_Pulse = defPluse;                                       //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM  
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                    //����ʱ������ֵС��CCR2ʱΪ�͵�ƽ 
        TIM_OC2Init(TIM3, &TIM_OCInitStructure);                                    //ʹ��ͨ��2  

        /* PWM1 Mode configuration: Channel3 */  
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
        TIM_OCInitStructure.TIM_Pulse = defPluse;                                       //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM  
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                    //����ʱ������ֵС��CCR2ʱΪ�͵�ƽ 
        TIM_OC3Init(TIM3, &TIM_OCInitStructure); 

        /* PWM1 Mode configuration: Channel3 */  
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
        TIM_OCInitStructure.TIM_Pulse = defPluse;                                       //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM  
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                    //����ʱ������ֵС��CCR2ʱΪ�͵�ƽ 
        TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
        
        TIM_Cmd(TIM3, ENABLE); 
        TIM_CtrlPWMOutputs(TIM3, ENABLE);
    }
    
}

void HalPwmInitialize(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
    /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */ 
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // ����������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOC, &GPIO_InitStructure);     
}

void HalPwmPoll(void)
{
}
