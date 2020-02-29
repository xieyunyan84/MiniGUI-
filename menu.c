
//----------------------------------------------------
//            界面处理模块
//            
//         
//
//    
//   
//
//          
//     
//
//                  
//
//
//-------------------------------------------------
// 
// 界面处理 Module:	KEY	  
//  :      
// /: 
// :         
// by:               
// Date:			  
// System;           
//-------------------------------------------------
// 
// 修改人   ：解云雁   
// 修改日期 ：2014.3.4
//----------------------------------------------------


#include "config.h" 

uint8   Key_fun;
uint8   count_update_lcd;



typedef struct{
 uint8  WINDOS_ID; 
 uint8  LCD_ID;
 uint8  MENU_ID;
 uint8  MENU_ID_MAX;
 uint8  WINDOS_Attribute;
 
 uint8  up_index;
 uint8  down_index;
 uint8  enter_index;
 uint8  esc_index;
 uint8  left_index;
 uint8  right_index;
 void (*operate)(); 
 uint8 *Dtat_Buf;
 } Key_index_struct;


uint8 Set_Time_Buf[14]={0};
uint8 Read_Time_Buf[14]={0}; 


 void (*operate)(uint8 *Databuf); 
 void (*Key_fun_Pt)(uint8 *Buf);
 //uint8   ID          虚拟总窗口   1 2 3 4 5 6
 //uint8   WINDOS_ID;  真实总窗口   1  2  3  5 6
 //uint8   MENU_ID     当前菜单号   1 2 3 4
 //uint8   MENU_ID_MAX
 //uint8   WINDOS_Attribute  当前界面属性   1显示   2 菜单   3  设置  4滚动 0未知
 
 //uint8  up_index;           按下“上”  跳到的界面
 //uint8  down_index;         按下“下”  跳到的界面
 //uint8  enter_index;        按下“确认”跳到的界面
 //uint8  esc_index;          按下“退出”跳到的界面
 //uint8  left_index;         按下“左”  跳到的界面
 //uint8  right_index;        按下“右”  跳到的界面
 //uint8  Data_Buf[]          数据
Key_index_struct  Key_tab[27]={
 {0,0,0,0,0,  0, 0, 0,  0,0,0,0,0},
 {1,1,0,0,1,  0, 0, 2,  0,0,0,(*Winons_1),0},  //登录界面
 
 //主菜单界面
 {2,2,1,0,2,  6, 3, 7, 1,0,0,(*Winons_2_1),0},//主菜单界面1
 {3,2,2,0,2,  2, 4, 8, 1,0,0,(*Winons_2_2),0},//主菜单界面2
 {4,2,3,0,2,  3, 5, 9, 1,0,0,(*Winons_2_3),0},//菜单界面3
 {5,2,4,0,2,  4, 6, 10, 1,0,0,(*Winons_2_4),0},//主菜单界面4
 {6,2,5,0,2,  5, 2, 11, 1,0,0,(*Winons_2_5),0}, //主菜单界面5

 
 //二级菜单对应的界面
 {7,3,0,0,1,  0,  0,  12, 2,0,0,(*Winons_3_1),0},//3手动切换
 {8,4,0,0,1,  0,  0,  0,  2,0,0,(*Winons_4_1),0},//4线路数据
 {9,5,1,0,4,  17, 14, 0,  2,0,0,(*Winons_5_1_1),0},//5故障记录
 {10,6,1,0,2,  22, 19, 23, 2,0,0,(*Winons_6_1),0},  //6传动操作
 {11,7,0,12,3,  11,  11,  24, 2,11,11,(*Winons_7_1),Set_Time_Buf},  //7设置时间


 //3界面下的
 {12,3,0,0,1,  0, 0, 12, 7,0,0,(*Winons_3_1_OK)},
 //4界面下的  空
 
 //5界面下的处理函数
 {13,5,1,0, 4,  17, 14, 0, 2,0,0,(*Winons_5_1_1)},
 {14,5,2,0, 4,  13, 15, 0, 2,0,0,(*Winons_5_1_2)},
 {15,5,3,0, 4,  14, 16, 0, 2,0,0,(*Winons_5_1_3)},
 {16,5,4,0, 4,  15, 17, 0, 2,0,0,(*Winons_5_1_4)},
 {17,5,5,0, 4,  16, 13, 0, 2,0,0,(*Winons_5_1_5)},
  
  //6界面下的处理函数
 {18,6,1,0, 2,  22, 19, 23, 2,0,0,(*Winons_6_1)},
 {19,6,2,0, 2,  18, 20, 23, 2,0,0,(*Winons_6_2)},
 {20,6,3,0, 2,  19, 21, 23, 2,0,0,(*Winons_6_3)},
 {21,6,4,0, 2,  20, 22, 23, 2,0,0,(*Winons_6_4)},
 {22,6,5,0, 2,  21, 18, 23, 2,0,0,(*Winons_6_5)},
  
  //8界面下的处理函数
 {23,3,0,0, 1,  0, 0, 18, 3,0,0,(*Winons_6_1_OK)},
  
  
 {24,6,5,0, 2,  21, 21, 18, 13,0,0,(*Winons_7_1_OK)},
 
 

 };

 







/*********************************************
* FUN:  void Menu_NEW(void)
*  菜单函数
* 
* 
* 
* 

* 
* 
* 
*
**********************************************/


 
 void Menu_NEW(void)
 {
   uint8 temp ;

   temp  = Key_fun;
   if(Key_Value!=0)
   { 
    switch(Key_Value)//010
          {
            case KEY_ENTER : Key_fun=Key_tab[Key_fun].enter_index;
                             break;
    
            case KEY_UP    : Key_fun=Key_tab[Key_fun].up_index;
                            if(Key_tab[Key_fun].WINDOS_Attribute == 3)
                              {
                              Key_tab[Key_fun].Dtat_Buf[Key_tab[Key_fun].MENU_ID] = (Key_tab[Key_fun].Dtat_Buf[Key_tab[Key_fun].MENU_ID]+1)%10;
                              }
                             break;
                             
            case KEY_DOWN  : Key_fun=Key_tab[Key_fun].down_index;
                             if(Key_tab[Key_fun].WINDOS_Attribute == 3)
                              {
                              if(Key_tab[Key_fun].Dtat_Buf[Key_tab[Key_fun].MENU_ID]==0)
                                  {Key_tab[Key_fun].Dtat_Buf[Key_tab[Key_fun].MENU_ID] = 9;}
                              else{
                                  Key_tab[Key_fun].Dtat_Buf[Key_tab[Key_fun].MENU_ID] = (Key_tab[Key_fun].Dtat_Buf[Key_tab[Key_fun].MENU_ID]-1)%10;
                                  }
                               }
                              break;
                             
            case KEY_LEFT  : Key_fun=Key_tab[Key_fun].left_index;
                             if(Key_tab[Key_fun].WINDOS_Attribute == 3)
                             {    
                               if(Key_tab[Key_fun].MENU_ID >= 1) {Key_tab[Key_fun].MENU_ID = (Key_tab[Key_fun].MENU_ID -1)%Key_tab[Key_fun].MENU_ID_MAX;}
                               else {Key_tab[Key_fun].MENU_ID =Key_tab[Key_fun].MENU_ID_MAX-1;}
                               *( Key_tab[Key_fun].Dtat_Buf+(Key_tab[Key_fun].MENU_ID_MAX))  = Key_tab[Key_fun].MENU_ID;
                             }
                            break;
                             
           case KEY_RIGHT :   
                            Key_fun=Key_tab[Key_fun].right_index;
                            if(Key_tab[Key_fun].WINDOS_Attribute == 3)
                             {   
                             if(Key_tab[Key_fun].MENU_ID < Key_tab[Key_fun].MENU_ID_MAX) {Key_tab[Key_fun].MENU_ID = (Key_tab[Key_fun].MENU_ID +1)%Key_tab[Key_fun].MENU_ID_MAX;}
                               else {Key_tab[Key_fun].MENU_ID = 0;}
                               *( Key_tab[Key_fun].Dtat_Buf+(Key_tab[Key_fun].MENU_ID_MAX))  = Key_tab[Key_fun].MENU_ID;
                             }
                            break;
 	    
            case KEY_ESC:    Key_fun=Key_tab[Key_fun].esc_index;
                             break;
             
            default :      Key_fun = Key_fun;break;
           
          } 
  
  
  
  
  if(Key_fun != 0) 
  {
    Key_fun_Pt=Key_tab[Key_fun].operate;
   (*Key_fun_Pt)(Key_tab[Key_fun].Dtat_Buf);//执行当前按键的操作
  }
  else
   {
   Key_fun = temp;
   }
   Key_Value = 0;
  }else
  {
  if(F_3S == 1)
  {
      //
  }
  
  }
   
   
 }
 