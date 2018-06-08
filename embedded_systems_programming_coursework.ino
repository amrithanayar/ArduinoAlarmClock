#
include < LiquidCrystal.h > #include < Adafruit_RGBLCDShield.h > #include < utility / Adafruit_MCP23017.h > #include < Wire.h > #include < Time.h > #include < TimeLib.h >
  Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();#
define RED 0x1# define YELLOW 0x3# define GREEN 0x2# define TEAL 0x6# define BLUE 0x4# define VIOLET 0x5# define WHITE 0x7
boolean menu = false;
boolean setcurrenttime = false;
boolean setalarmtime = false;
int sethour = 0;
int setminute = 0;
int setsecond = 0;
int cursor = 0;
int setalarmhour = 0;
int setalarmminute = 0;
int setalarmsecond = 0;
boolean alarm = false;
boolean alarmisgoingoff = false;
boolean turnoffsnooze = false;
boolean seealarmtime = false;
boolean seealarmstate = false;
int menuscroll = 0;
boolean scroll = false;

void digitalClockDisplay() { //function to print the digital clock display of the time(used in lab session)

  lcd.setCursor(4, 0);
  lcd.print(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(":");
  printDigits(second());

}

void printDigits(int digits) { //function to print values of time (used in lab session)
  // utility function for digital clock display: prints preceding colon and leading 0
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

void printsettime() { //function to print the time when user is trying to change current time
  lcd.setCursor(0, 0);
  lcd.print("set current time");
  lcd.setCursor(4, 1);
  printDigits(sethour);

  lcd.print(":");

  printDigits(setminute);
  lcd.print(":");
  printDigits(setsecond);

}
void printsetalarmtime() { //function to print the alarm time
  if (setalarmtime == true) {
    lcd.setCursor(1, 0);
    lcd.print("Set alarm time");
  } else if (seealarmtime == true) {
    lcd.setCursor(1, 0);
    lcd.print("Alarm time is:");
  }

  lcd.setCursor(4, 1);
  printDigits(setalarmhour);
  lcd.print(":");
  printDigits(setalarmminute);
  lcd.print(":");
  printDigits(setalarmsecond);

}
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 3);

  setTime(0, 0, 0, 22, 02, 2017); //set the inital time for when program is first starting up

}
void loop() {
  if ((setalarmhour == hour() && setalarmminute == minute()) && (setalarmsecond == second() && alarm == true)) { //if statement to determine if the current time is the same as alarm time to trigger alarm
    menu = false; //so that when the alarm is triggering the default display is not shown
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*ALARM*  *ALARM*");
    lcd.setCursor(0, 1);
    lcd.print("Click Any Button");
    alarmisgoingoff = true; //state so that the buttons can react to the alarm
  }
  if (alarmisgoingoff == true) {
    lcd.setBacklight(RED); //setting backlight of alarm to red to draw users attemtion
  }
  if ((menu == false && alarmisgoingoff == false) && turnoffsnooze == false) { //to determine when the alarm clock should be in default state
    lcd.setBacklight(WHITE); //clarifying background colour so that if alarm clock goes back to default state after the alarm sounding the background is not red
    digitalClockDisplay();
    lcd.setCursor(0, 1);
    lcd.print("Select for menu"); //instructions for user to access menu
  }
  if (((menu == true && seealarmstate == false) && (seealarmtime == false && setcurrenttime == false)) && setalarmtime == false) { //to determine when the alarm clock is in the menu state
    scroll = true;

  }
  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    if (buttons & BUTTON_UP) {
      if (alarmisgoingoff == true) { //so button functionality changes when the alarm is going off
        lcd.clear();
        alarmisgoingoff = 0;
        turnoffsnooze = 1;
        lcd.setCursor(0, 0);
        lcd.print("Left to snooze");
        lcd.setCursor(0, 1);
        lcd.print("Right to off");
      } else if (scroll == true) { //so button functionality can change whilst in the main menu state
        if (menuscroll == 0) { // so that user can scroll through functionality the display changes depending on the menuscroll value

        } else if (menuscroll == 1) { //menuscroll value is decremented by 1

          lcd.clear();
          menuscroll = 0;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(0, 1);
          lcd.print("Scroll with Keys");

        } else if (menuscroll == 2) {
          lcd.clear();
          menuscroll = 1;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(1, 1);
          lcd.print("See alarm Time");
        } else if (menuscroll == 3) {
          lcd.clear();
          menuscroll = 2;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(1, 1);
          lcd.print("Set alarm time");
        } else if (menuscroll == 4) {
          lcd.clear();
          menuscroll = 3;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(0, 1);
          lcd.print("Set alarm on/off");
        } else if (menuscroll == 5) {
          lcd.clear();
          menuscroll = 4;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(0, 1);
          lcd.print("Set current time");
        }

      } else if (setcurrenttime == true) { //so functionality of buttons changes when user is setting current time
        if (cursor == 0) { //user is changing hour value
          sethour++;
          if (sethour >= 24) {
            sethour = 0;
          }
        } else if (cursor == 1) { //user is changing minute value
          setminute++;
          if (setminute >= 60) {
            setminute = 0;
          }
        } else if (cursor == 2) { //user is changing second value
          setsecond++;
          if (setsecond >= 60) {
            setsecond = 0;
          }
        }
        printsettime(); //display the time being set as it is being changes
      } else if (setalarmtime == true) { //so functionality of buttons can change when user is setting alarm
        if (cursor == 0) {. //user is changing alarm hour value
          setalarmhour++;
          if (setalarmhour >= 24) {
            setalarmhour = 0;
          }
        } else if (cursor == 1) { //user is changing alarm minute value
          setalarmminute++;
          if (setalarmminute >= 60) {
            setalarmminute = 0;
          }
        } else if (cursor == 2) { //user is changing alarm second value
          setalarmsecond++;
          if (setalarmsecond >= 60) {
            setalarmsecond = 0;
          }
        }
        printsetalarmtime();
      }
    }
    if (buttons & BUTTON_DOWN) {
      if (alarmisgoingoff == true) { //when alarm is going off
        lcd.clear();
        alarmisgoingoff = 0;
        turnoffsnooze = true;
        lcd.setCursor(0, 0);
        lcd.print("Left to snooze");
        lcd.setCursor(0, 1);
        lcd.print("Right to off");
      } else if (turnoffsnooze == true) {
        when the snooze menu is displayed

      } else if (scroll == true) { //when user is scrolling through main menu
        if (menuscroll == 0) { //menuscroll value is incremented by one and lcd display changes accordingly
          lcd.clear();
          menuscroll = 1;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(1, 1);
          lcd.print("See alarm time");

        } else if (menuscroll == 1) {
          lcd.clear();
          menuscroll = 2;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(1, 1);
          lcd.print("Set alarm time");

        } else if (menuscroll == 2) {
          lcd.clear();
          menuscroll = 3;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(0, 1);
          lcd.print("Set alarm on/off");

        } else if (menuscroll == 3) {
          lcd.clear();
          menuscroll = 4;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(0, 1);
          lcd.print("Set Current time$");

        } else if (menuscroll == 4) {
          lcd.clear();
          menuscroll = 5;
          lcd.setCursor(3, 0);
          lcd.print("MAIN MENU");
          lcd.setCursor(1, 1);
          lcd.print("Exit Main Menu");

        } else if (menuscroll == 5) {

        }

      } else if (setcurrenttime == true) { //when user is trying to set the current time
        if (cursor == 0) { //cursor value is decremented by one as user changes between changing the hour, second, and minute values
          sethour--;
          if (sethour < 0) {
            sethour = 23;
          }
        } else if (cursor == 1) {
          setminute--;
          if (setminute < 0) {
            setminute = 59;
          }

        } else if (cursor == 2) {
          setsecond--;
          if (setsecond < 0) {
            setsecond = 59;
          }
        }
        printsettime();
      } else if (setalarmtime == true) { // user is trying to set the alarm time
        if (cursor == 0) { //cursor values are decremented as user tries to change hour, minute or second
          setalarmhour--;
          if (setalarmhour < 0) {
            setalarmhour = 23;
          }
        }
        if (cursor == 1) {
          setalarmminute--;
          if (setalarmminute < 0) {
            setalarmminute = 59;
          }

        }
        if (cursor == 2) {
          setalarmsecond--;
          if (setalarmsecond < 0) {
            setalarmsecond = 59;
          }
        }
        printsetalarmtime();
      }

    }
    if (buttons & BUTTON_RIGHT) {
      if (alarmisgoingoff == true) { //functionality for when alarm is going off
        lcd.clear();
        alarmisgoingoff = 0;
        turnoffsnooze = true;
        lcd.setCursor(1, 0);
        lcd.print("Left to snooze");
        lcd.setCursor(2, 1);
        lcd.print("Right to off");
      } else if (turnoffsnooze == true) { //functionality for when user is trying to dismiss alarm
        lcd.clear();
        lcd.print("Alarm has been dismissed");
        for (int scrollCounter = 0; scrollCounter < 20; scrollCounter++) //display confirming that user has dismissed the alarm
        {

          lcd.scrollDisplayLeft();

          delay(450);
        }
        lcd.clear();
        turnoffsnooze = false;
        menu = false;

      } else if (setcurrenttime == true) { //user is trying to set current time
        if (cursor == 0) { //cursor calue is incremented

          cursor = 1;

        } else if (cursor == 1) {

          cursor = 2;

        } else if (cursor == 2) {
          cursor = 2;
        }

        printsettime();
      } else if (setalarmtime == true) { //when user is trying to set alarmtime
        if (cursor == 0) { //cursor value is incremented
          cursor = 1;
        } else if (cursor == 1) {
          cursor = 2;
        } else if (cursor == 2) {
          cursor = 2;
        }
        printsetalarmtime();
      }

    }
    if (buttons & BUTTON_LEFT) {
      if (alarmisgoingoff == true) { //when alarm is going off
        lcd.clear();
        alarmisgoingoff = 0;
        turnoffsnooze = true;
        lcd.setCursor(0, 0);
        lcd.print("Left to snooze");
        lcd.setCursor(0, 1);
        lcd.print("Right to off");
      } else if (turnoffsnooze == true) { //when user wants to snooze the alarm
        lcd.clear();
        lcd.print("Alarm will now snooze for 30 seconds"); //confirmation of snooze
        for (int scrollCounter = 0; scrollCounter < 20; scrollCounter++) {

          lcd.scrollDisplayLeft();

          delay(450);
        }
        lcd.clear();
        setalarmsecond = second() + 30; //setting new alarmtime to current time+30secs
        if (setalarmsecond >= 60) {
          setalarmsecond = setalarmsecond - 60; //use current time
          setalarmminute = minute() + 1;

        }
        if (setalarmminute >= 60) {
          setalarmminute = setalarmminute - 60;
          setalarmhour = hour() + 1;
        }
        if (setalarmhour >= 24) {
          setalarmhour = setalarmhour - 24;
        }
        menu = false;
        alarm = true;
        turnoffsnooze = false;

      } else if (setcurrenttime == true) { //setting current time is menu
        if (cursor == 0) {
          cursor = 0;

        } else if (cursor == 1) { //decrement cursor value
          cursor = 0;

        } else if (cursor = 2) {
          cursor = 1;
        }

        printsettime();
      } else if (setalarmtime == true) { //setting alarm from main menu
        if (cursor == 0) {
          cursor = 0;
        } else if (cursor == 1) { //cursor is decremented
          cursor = 0;
        } else if (cursor == 2) {
          cursor = 1;
        }
        printsetalarmtime();
      } else if (seealarmstate == true) {
        user is trying to see alarmstate from main menu
        if (alarm == false) { //user wants to turn on alarm
          lcd.clear();
          lcd.print("The alarm has been turned on"); //confirmation message
          for (int scrollCounter = 0; scrollCounter < 25; scrollCounter++) {

            lcd.scrollDisplayLeft();

            delay(450);
          }
          alarm = true;
          lcd.clear();
          seealarmstate = false;
        } else if (alarm == true) { //user wants to turn off alarm
          lcd.clear();
          lcd.print("The alarm has been turned off"); //confirmation message
          for (int scrollCounter = 0; scrollCounter < 25; scrollCounter++) {

            lcd.scrollDisplayLeft();

            delay(450);
          }
          lcd.clear();
          alarm = false;
          seealarmstate = false;
        }
        lcd.clear(); // once alarm state is changes display returns back to default
        menuscroll = 0;
        menu = true;
        lcd.setCursor(3, 0);
        lcd.print("MAIN MENU");
        lcd.setCursor(0, 1);
        lcd.print("Scroll with Keys");
      }

    }

  }

  if (buttons & BUTTON_SELECT) {
    if (alarmisgoingoff == true) { //is alarm is going off
      lcd.clear();
      alarmisgoingoff = 0;
      turnoffsnooze = true;
      lcd.setCursor(0, 0);
      lcd.print("Left to snooze");
      lcd.setCursor(0, 1);
      lcd.print("Right to off");
    } else if (turnoffsnooze == true) { //if alarm is in snooze display
      alarmisgoingoff = 0;
      turnoffsnooze = 1;
      lcd.setCursor(0, 0);
      lcd.print("Left to snooze");
      lcd.setCursor(0, 1);
      lcd.print("Right to off");
    } else if (menu == false) { // function so when in default display and select is pressed menu state is activated
      menuscroll = 0;
      menu = true;
      lcd.setCursor(3, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print("Scroll with keys");
    } else if (menu == true && scroll == true) { //fucntion so user can choose functionality
      if (menuscroll == 1) { //see alarm time functionality is chosen
        scroll = false;
        seealarmtime = true;
        lcd.clear();
        printsetalarmtime();

      }
      if (menuscroll == 2) { //set alarm time functionality is chosen
        scroll = false;
        lcd.clear();
        setalarmtime = true;
        printsetalarmtime();
      }
      if (menuscroll == 3) { //see alarm state functionality is chosen
        scroll = false;
        lcd.clear();
        seealarmstate = true;
        if (alarm == true) {
          lcd.setCursor(2, 0);
          lcd.print("ALARM IS ON");
          lcd.setCursor(0, 1);
          lcd.print("Push left to off");
        } else if (alarm == false) {
          scroll = false;
          lcd.setCursor(2, 0);
          lcd.print("ALARM IS OFF");
          lcd.setCursor(0, 1);
          lcd.print("Push left to on");
        }
      }
      if (menuscroll == 4) { //set current time functionality is chosen
        scroll = false;
        lcd.clear();
        setcurrenttime = true;
        printsettime();
      }
      if (menuscroll == 5) { // user has chosen to exit the menu
        lcd.clear();
        menu = false;
        scroll = false;

      }

    } else if (setcurrenttime == true) { //user wants to set the current time
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The current time has been reset"); //confirmation messave
      for (int scrollCounter = 0; scrollCounter < 20; scrollCounter++) {

        lcd.scrollDisplayLeft();

        delay(450);
      }
      lcd.clear();
      setcurrenttime = false;
      menu = true;
      lcd.clear();
      menuscroll = 0;
      menu = true;
      lcd.setCursor(3, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print("Scroll with keys");
      setTime(sethour, setminute, setsecond, 22, 02, 2017); //current time is set to that of the users choice

    } else if (setalarmtime == true) { //user wants to set alarm time
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The alarm time has been reset");
      for (int scrollCounter = 0; scrollCounter < 25; scrollCounter++) //confirmation message
      {

        lcd.scrollDisplayLeft();

        delay(450);
      }

      lcd.clear();
      setalarmtime = false; //exit set alarm time state
      lcd.clear();
      menuscroll = 0;
      menu = true;
      lcd.setCursor(3, 0);
      lcd.print("MAIN MENU"); //return display to main menu
      lcd.setCursor(0, 1);
      lcd.print("Scroll with keys");
      Serial.print(setalarmminute);
    } else if (seealarmstate == true) { //if user doesnt want to change alarm state after viewing it
      lcd.clear();
      seealarmstate = false;
      lcd.clear();
      menuscroll = 0;
      menu = true;
      lcd.setCursor(3, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print("Scroll with keys");
    } else if (seealarmtime == true) { // for user to exit the seeing alarm time state
      lcd.clear();
      seealarmtime = false;
      lcd.clear();
      menuscroll = 0;
      menu = true;
      lcd.setCursor(3, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print("Scroll with keys");
    }
  }

}

