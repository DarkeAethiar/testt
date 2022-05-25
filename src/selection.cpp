#include "selection.hpp"
#include "display/lvgl.h"
// #include "robot/config/controller_config.hpp"
// #include "routines.hpp"
#include <algorithm>
#include <string>
#include <iostream>
#include "main.hpp"


//void AutonWinPointRight();

namespace auton {
  namespace selection {
    /*forward defs*/
    void StyleInit();
    void BtnInit(lv_obj_t *btn, lv_style_t *sty, int row, int col);
    void BtnShow();

    std::string RoutsToString(int one, int two);
    void ControllerScreen();
    void testBtnPos(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Positons Positon);
    void testBtnSho(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Shoots Shoot);
    void testBtnFla(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Flags Flag);
    void testBtnOpt(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Options Option);

    static lv_res_t OnClickPos(_lv_obj_t *pressedBtn);
    static lv_res_t OnClickSho(_lv_obj_t *pressedBtn);
    static lv_res_t OnClickFla(_lv_obj_t *pressedBtn);
    static lv_res_t OnClickOpt(_lv_obj_t *pressedBtn);

    lv_obj_t *Btn0_0 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn1_0 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn2_0 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn3_0 = lv_btn_create(lv_scr_act(), NULL);

    lv_obj_t *Btn0_1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn1_1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn2_1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn3_1 = lv_btn_create(lv_scr_act(), NULL);

    lv_obj_t *Btn0_2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn1_2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn2_2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t *Btn3_2 = lv_btn_create(lv_scr_act(), NULL);

    lv_style_t style_red;
    lv_style_t style_blue;
    lv_style_t style_config;
    // lv_style_t style_btn;

    Positons positon = Positons::NONE;//br skills; fr match;
    Shoots shoot = Shoots::MID;
    Flags flag = Flags::TOP;
    Options option = Options::PARK;

    std::string screenText[4][3] = {
        {"Right1/2WP", "FullWP", "Empty"},
        {"Right2G", "RightMid1/2WP", "Empty"},
        {"Left1/2WP", "Empty", "Empty"},
        {"Left2G", "Empty", "Empty"},
    };
    // AutonRight();
  // AutonLeft();
  // Autonsuperultimatewinpointthatmadeethanwanttohanghimself();
  // AutonWinPointRight();
  // AutonWinPointLeft();
  // AutonSkills();
  //  AutonFullWinpoint();
  
    void execute() {
      switch (positon) {
      case Positons::r1:
        AutonWinPointRight();
        break;
      case Positons::r2:
        AutonRight();
        break;
      case Positons::l1:
        AutonWinPointLeft();
        break;
      case Positons::l2:
        AutonLeft();
        break;
      case Positons::l3:
      AutonFullWinpoint();
        break;
      case Positons::r4:
      AutonRightMidWinpoint();
        break;
      }
    }
    void screenInit() {
      StyleInit();

      BtnInit(Btn0_0, &style_red, 0, 0);
      BtnInit(Btn1_0, &style_red, 1, 0);
      BtnInit(Btn2_0, &style_red, 2, 0);
      BtnInit(Btn3_0, &style_red, 3, 0);
      lv_btn_set_action(Btn0_0, LV_BTN_ACTION_CLICK, OnClickPos);
      lv_btn_set_action(Btn1_0, LV_BTN_ACTION_CLICK, OnClickPos);
      lv_btn_set_action(Btn2_0, LV_BTN_ACTION_CLICK, OnClickPos);
      lv_btn_set_action(Btn3_0, LV_BTN_ACTION_CLICK, OnClickPos);

      BtnInit(Btn0_1, &style_config, 0, 1);
      BtnInit(Btn0_2, &style_config, 0, 2);
      lv_btn_set_action(Btn0_1, LV_BTN_ACTION_CLICK, OnClickPos);
      lv_btn_set_action(Btn0_2, LV_BTN_ACTION_CLICK, OnClickPos);

      BtnInit(Btn1_1, &style_config, 1, 1);
      BtnInit(Btn2_1, &style_config, 2, 1);
      lv_btn_set_action(Btn1_1, LV_BTN_ACTION_CLICK, OnClickPos);
      lv_btn_set_action(Btn2_1, LV_BTN_ACTION_CLICK, OnClickPos);

      BtnInit(Btn3_1, &style_config, 3, 1);
      lv_btn_set_action(Btn3_1, LV_BTN_ACTION_CLICK, OnClickPos);

      BtnInit(Btn1_2, &style_config, 1, 2);
      BtnInit(Btn2_2, &style_config, 2, 2);
      BtnInit(Btn3_2, &style_config, 3, 2);

      BtnShow();
      std::cout << "pos: " << static_cast<int>(positon) << " sho: " << static_cast<int>(shoot) << " fla: " << static_cast<int>(flag) << " opt: " << static_cast<int>(option) << std::endl;
    }
    void StyleInit() {
      lv_style_copy(&style_red, &lv_style_plain);
      style_red.text.color = LV_COLOR_HEX(0xFF0000);

      lv_style_copy(&style_blue, &lv_style_plain);
      style_blue.text.color = LV_COLOR_HEX(0x0000FF);

      lv_style_copy(&style_config, &lv_style_plain);
      style_config.text.color = LV_COLOR_HEX(0x00FF00);

      // lv_style_copy(&style_btn, &lv_style_plain);
    }
    void BtnInit(lv_obj_t *btn, lv_style_t *sty, int row, int col) {
      lv_obj_t *label;
      int x = 465 / 3 * col;
      int y = 240 / 4 * row;
      lv_btn_set_toggle(btn, true);
      lv_obj_set_pos(btn, x, y);
      lv_obj_set_size(btn, 465 / 3, 240 / 4);
      // lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, click());

      label = lv_label_create(btn, NULL);
      lv_obj_set_style(label, sty);
      lv_label_set_text(label, screenText[row][col].c_str());

      std::cout << "Btn on row " << row << " and col " << col << " Inited";
      if (sty == &style_red)
        std::cout << "red" << std::endl;
      else
        std::cout << "blue" << std::endl;
    }
    std::string RoutsToString(int one, int two) {
      return screenText[one][two];
    }

    void ControllerScreen() {
    //   controllerMaster.setText(0, 0, "");
    }
    void testBtnPos(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Positons Positon) {
      if (pressedBtn == Btn) {
        positon = Positon;
      } else {
        lv_btn_set_state(Btn, LV_BTN_STATE_REL);
      }
    }
    void testBtnSho(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Shoots Shoot) {
      if (pressedBtn == Btn) {
        shoot = Shoot;
      } else {
        lv_btn_set_state(Btn, LV_BTN_STATE_REL);
      }
    }
    void testBtnFla(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Flags Flag) {
      if (pressedBtn == Btn) {
        if (Flag == Flags::TOP) {
          switch (flag) {
          case Flags::BOTH:
            flag = Flags::MID;
            lv_btn_set_state(Btn, LV_BTN_STATE_REL);
            break;
          case Flags::HOLD:
            flag = Flags::TOP;
            break;
          case Flags::TOP:
            flag = Flags::HOLD;
            lv_btn_set_state(Btn, LV_BTN_STATE_REL);
            break;
          case Flags::MID:
            flag = Flags::BOTH;
            break;
          case Flags::NONE:
            flag = Flags::TOP;
            break;
          }
        } else {
          switch (flag) {
          case Flags::BOTH:
            flag = Flags::TOP;
            lv_btn_set_state(Btn, LV_BTN_STATE_REL);
            break;
          case Flags::HOLD:
            flag = Flags::MID;
            break;
          case Flags::TOP:
            flag = Flags::BOTH;
            break;
          case Flags::MID:
            flag = Flags::HOLD;
            lv_btn_set_state(Btn, LV_BTN_STATE_REL);
            break;
          case Flags::NONE:
            flag = Flags::MID;
            break;
          }
        }
      } // namespace selection
      else {
        // lv_btn_set_state(Btn, LV_BTN_STATE_REL);
      }
    } // namespace auton
    void testBtnOpt(_lv_obj_t *pressedBtn, _lv_obj_t *Btn, Options Option) {
      if (pressedBtn == Btn) {
        switch (option) {
        case Options::PARK:
          option = Options::NPARK;
          break;
        case Options::NPARK:
          option = Options::PARK;
          break;
        case Options::NONE:
          option = Options::PARK;
          break;
        }
      } else {
        lv_btn_set_state(Btn, LV_BTN_STATE_REL);
      }
    }
    static lv_res_t OnClickPos(_lv_obj_t *pressedBtn) {
      testBtnPos(pressedBtn, Btn0_0, Positons::r1);
      testBtnPos(pressedBtn, Btn1_0, Positons::r2);
      //testBtnPos(pressedBtn, Btn1_1, Positons::r3);
      testBtnPos(pressedBtn, Btn2_0, Positons::l1);
      testBtnPos(pressedBtn, Btn3_0, Positons::l2);
      testBtnPos(pressedBtn, Btn0_1, Positons::l3);
      testBtnPos(pressedBtn, Btn1_1, Positons::r4);
      ControllerScreen();
      std::cout << "pos: " << static_cast<int>(positon) << " sho: " << static_cast<int>(shoot) << " fla: " << static_cast<int>(flag) << " opt: " << static_cast<int>(option) << std::endl;
      return LV_RES_OK;
    }
    static lv_res_t OnClickSho(_lv_obj_t *pressedBtn) {
      testBtnSho(pressedBtn, Btn0_1, Shoots::MID);
      testBtnSho(pressedBtn, Btn0_2, Shoots::FAR);
      ControllerScreen();
      std::cout << "pos: " << static_cast<int>(positon) << " sho: " << static_cast<int>(shoot) << " fla: " << static_cast<int>(flag) << " opt: " << static_cast<int>(option) << std::endl;
      return LV_RES_OK;
    }
    static lv_res_t OnClickFla(_lv_obj_t *pressedBtn) {
      testBtnFla(pressedBtn, Btn1_1, Flags::TOP);
      testBtnFla(pressedBtn, Btn2_1, Flags::MID);
      ControllerScreen();
      std::cout << "pos: " << static_cast<int>(positon) << " sho: " << static_cast<int>(shoot) << " fla: " << static_cast<int>(flag) << " opt: " << static_cast<int>(option) << std::endl;
      return LV_RES_OK;
    }
    static lv_res_t OnClickOpt(_lv_obj_t *pressedBtn) {
      testBtnOpt(pressedBtn, Btn3_1, Options::PARK);
      ControllerScreen();
      std::cout << "pos: " << static_cast<int>(positon) << " sho: " << static_cast<int>(shoot) << " fla: " << static_cast<int>(flag) << " opt: " << static_cast<int>(option) << std::endl;
      return LV_RES_OK;
    }

    void BtnShow() {
      switch (positon) {
      case Positons::r1:
        lv_btn_set_state(Btn0_0, LV_BTN_STATE_TGL_PR); //fr
        break;
      case Positons::r2:
        lv_btn_set_state(Btn1_0, LV_BTN_STATE_TGL_PR); //br
        break;
      case Positons::l1:
        lv_btn_set_state(Btn2_0, LV_BTN_STATE_TGL_PR); //bb
        break;
      case Positons::l2:
        lv_btn_set_state(Btn3_0, LV_BTN_STATE_TGL_PR); //fb
        break;
      case Positons::l3:
        lv_btn_set_state(Btn1_0, LV_BTN_STATE_TGL_PR);
        break;
      case Positons::r4:
        lv_btn_set_state(Btn1_1, LV_BTN_STATE_TGL_PR);
        break;
      };
      switch (shoot) {
      case Shoots::FAR:
        lv_btn_set_state(Btn0_2, LV_BTN_STATE_TGL_PR); //far
        break;
      case Shoots::MID:
        lv_btn_set_state(Btn0_1, LV_BTN_STATE_TGL_PR); //mid
        break;
      }
      switch (flag) {
      case Flags::BOTH:
        lv_btn_set_state(Btn1_1, LV_BTN_STATE_TGL_PR); //top
        lv_btn_set_state(Btn2_1, LV_BTN_STATE_TGL_PR); //mid
        break;
      case Flags::TOP:
        lv_btn_set_state(Btn1_1, LV_BTN_STATE_TGL_PR); //top
        break;
      case Flags::MID:
        lv_btn_set_state(Btn2_1, LV_BTN_STATE_TGL_PR); //mid
        break;
      }
      switch (option) {
      case Options::PARK:
        lv_btn_set_state(Btn3_1, LV_BTN_STATE_TGL_PR); //park
        break;
      case Options::NPARK:
        break;
      };
    }
  } // namespace selection
} // namespace auton
