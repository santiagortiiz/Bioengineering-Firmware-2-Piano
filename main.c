/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

// Constantes: Fin/Fout

#define DO 137
#define DOS 130
#define RE 122
#define RES 116
#define MI 109
#define FA 103
#define FAS 97
#define SOL 92
#define SOLS 87
#define LA 82
#define LAS 77
#define SI 73

// Banderas
char bandPT=0;
char secuencia=0;
char caja_musical=0;

// Funciones
CY_ISR(Piano);
CY_ISR(contador);

void Notas (char Nota);
void unravel();     // Cancion Unravel

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_Teclas_StartEx(Piano);
    isr_contador_StartEx(contador);
    PWM_Init();

    for(;;)
    {
        if (Teclas_Read()==0b0000 && bandPT==1)
        {
            PWM_Stop();
            bandPT=0;
            leds_Write(0b0000);
        }
        
        if (caja_musical==1)
        {
            cancion_Start();
            if(secuencia==1){Notas(RE);leds_Write(0b111);}
            if(secuencia==2){leds_Write(0b000);PWM_Stop();}
            if(secuencia==3){Notas(DO);leds_Write(0b001);}
            if(secuencia==4){leds_Write(0b000);PWM_Stop();}
            if(secuencia==5){Notas(LAS);leds_Write(0b011);}
            if(secuencia==6){leds_Write(0b000);PWM_Stop();}

            if(secuencia==8){Notas(LA);leds_Write(0b111);}
            if(secuencia==9){leds_Write(0b000);PWM_Stop();}
            if(secuencia==10){Notas(RE);leds_Write(0b100);}
            if(secuencia==11){leds_Write(0b000);PWM_Stop();}
            if(secuencia==12){Notas(DO);leds_Write(0b110);}
            if(secuencia==13){leds_Write(0b000);PWM_Stop();}
            // RE DO LAS, LA RE DO,

            if(secuencia==15){Notas(LAS);leds_Write(0b001);}
            if(secuencia==16){leds_Write(0b000);PWM_Stop();}
            if(secuencia==17){Notas(LA);leds_Write(0b010);}
            if(secuencia==18){leds_Write(0b000);PWM_Stop();}
            if(secuencia==19){Notas(RE);leds_Write(0b100);}
            if(secuencia==20){leds_Write(0b000);PWM_Stop();}

            // LAS LA RE X2
            if(secuencia==22){Notas(LAS);leds_Write(0b010);}
            if(secuencia==23){leds_Write(0b000);}
            if(secuencia==24){Notas(LA);leds_Write(0b001);}
            if(secuencia==25){leds_Write(0b000);}
            if(secuencia==26){Notas(RE);leds_Write(0b010);}
            if(secuencia==27){leds_Write(0b000);}
            if(secuencia==28){Notas(LAS);leds_Write(0b100);}
            if(secuencia==29){leds_Write(0b000);}
            if(secuencia==30){Notas(LA);leds_Write(0b101);}
            if(secuencia==31){leds_Write(0b000);}
            if(secuencia==32){Notas(RE);leds_Write(0b010);}    

            // SOL LA RE X2
            if(secuencia==34){leds_Write(0b000);PWM_Stop();}
            if(secuencia==35){Notas(SOL);leds_Write(0b101);}
            if(secuencia==36){leds_Write(0b000);PWM_Stop();}
            if(secuencia==37){Notas(LA);leds_Write(0b010);}
            if(secuencia==38){leds_Write(0b000);PWM_Stop();}
            if(secuencia==39){Notas(RE);leds_Write(0b111);}
            if(secuencia==40){leds_Write(0b000);PWM_Stop();}
            if(secuencia==41){Notas(SOL);leds_Write(0b100);}
            if(secuencia==42){leds_Write(0b000);PWM_Stop();}
            if(secuencia==43){Notas(LA);leds_Write(0b110);}
            if(secuencia==44){leds_Write(0b000);PWM_Stop();} 
            if(secuencia==45){Notas(RE);leds_Write(0b111);}
            if(secuencia==46){leds_Write(0b000);PWM_Stop();}

            // MI MI SOL SOL DO
            if(secuencia==50){Notas(MI);leds_Write(0b001);}
            if(secuencia==51){leds_Write(0b000);PWM_Stop();}
            if(secuencia==52){Notas(MI);leds_Write(0b011);}
            if(secuencia==53){leds_Write(0b000);PWM_Stop();}
            if(secuencia==54){Notas(SOL);leds_Write(0b100);}
            if(secuencia==55){leds_Write(0b000);PWM_Stop();}
            if(secuencia==56){Notas(SOL);leds_Write(0b001);}
            if(secuencia==57){leds_Write(0b000);PWM_Stop();}
            if(secuencia==58){Notas(DO);leds_Write(0b010);}
            if(secuencia==59){leds_Write(0b000);PWM_Stop();}

            //LA LAS LA MI FA 
            if(secuencia==63){Notas(LAS);leds_Write(0b101);}
            if(secuencia==64){leds_Write(0b000);PWM_Stop();}
            if(secuencia==65){Notas(LA);leds_Write(0b110);}
            if(secuencia==66){leds_Write(0b000);PWM_Stop();}
            if(secuencia==67){Notas(LA);leds_Write(0b011);}
            if(secuencia==68){leds_Write(0b000);PWM_Stop();}
            if(secuencia==69){Notas(MI);leds_Write(0b111);}
            if(secuencia==72){leds_Write(0b000);PWM_Stop();}
            if(secuencia==73){Notas(FA);leds_Write(0b111);}
            if(secuencia==80){leds_Write(0b000);PWM_Stop();caja_musical=0;}
        }
    }
}
void Notas (char Nota)
{
    PWM_WritePeriod(Nota);
    PWM_WriteCompare(Nota/2);
    PWM_Start();
}
      
CY_ISR(Piano)
{
    bandPT=1;
    if (Teclas_Read()==0b1000){
        Notas(MI);
        leds_Write(0b001);
    }
    else if(Teclas_Read()==0b0100){
        Notas(SOL);
        leds_Write(0b010);
    }
    else if(Teclas_Read()==0b0010){
        Notas(LA);
        leds_Write(0b100);
    }
    else if(Teclas_Read()==0b0001){
        leds_Write(0b111);
        secuencia=-2;
        caja_musical=1;
    }
}

CY_ISR(contador)
{
    secuencia++;
}
/* [] END OF FILE */