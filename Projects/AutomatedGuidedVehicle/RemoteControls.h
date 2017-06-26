#ifndef RemoteControl_h
#define RemoteControl_h

class RemoteControls
{
  String _command = "";
  long _code = 0;

  String _remoteType = "DEFAULT";

  void setCommand(long value)
  {
    _code = value;
    
    if (_remoteType == "DEFAULT" || _remoteType == "CARMP3")
    {
      switch (_code)
      {
        case 16753245:
          _command = "CH-";
          break;
        case 16736925:
          _command = "CH";
          break;
        case 16769565:
          _command = "CH+";
          break;
        case 16720605:
          _command = "PREV";
          break;
        case 16712445:
          _command = "NEXT";
          break;
        case 16761405:
          _command = "PLAY";
          break;
        case 16769055:
          _command = "VOL-";
          break;
        case 16754775:
          _command = "VOL+";
          break;
        case 16748655:
          _command = "EQ";
          break;
        case 16738455:
          _command = "0";
          break;
        case 16724175:
          _command = "1";
          break;
        case 16718055:
          _command = "2";
          break;
        case 16743045:
          _command = "3";
          break;
        case 16716015:
          _command = "4";
          break;
        case 16726215:
          _command = "5";
          break;
        case 16734885:
          _command = "6";
          break;
        case 16728765:
          _command = "7";
          break;
        case 16730805:
          _command = "8";
          break;
        case 16732845:
          _command = "9";
          break;
        case 16750695:
          _command = "100+";
          break;
        case 16756815:
          _command = "200+";
          break;
          
        default:
          Reset();
          break;
      }
    }
    if (_remoteType == "HUMAX")
    {
      switch (_code)
      {
        case 585743:
          _command = "CH-";
          break;
        case 526583:
          _command = "CH+";
          break;
        case 542903:
          _command = "LEFT";
          break;
        case 534743:
          _command = "RIGHT";
          break;
        case 559223:
          _command = "UP";
          break;
        case 567383:
          _command = "DOWN";
          break;          
        case 525053:
          _command = "VOL-";
          break;
        case 587783:
          _command = "VOL+";
          break;
        case 575543:
          _command = "OK";
          break;


        case 569423:
          _command = "TV";
          break;
        case 540863:
          _command = "SOURCE";
          break;
        case 524543:
          _command = "POWER";
          break;
        case 569933:
          _command = "LIST";
          break;
        case 579623:
          _command = "GUIDE";
          break;
        case 557693:
          _command = "BACK";
          break;
        case 551063:
          _command = "EXIT";
          break;

        case 553103:
          _command = "MENU";
          break;
        case 574013:
          _command = "INFO";
          break;
        case 530663:
          _command = "MUTE";
          break;


          
        case 536783:
          _command = "0";
          break;
        case 573503:
          _command = "1";
          break;
        case 532703:
          _command = "2";
          break;
        case 565343:
          _command = "3";
          break;
        case 549023:
          _command = "4";
          break;
        case 581663:
          _command = "5";
          break;
        case 528623:
          _command = "6";
          break;
        case 561263:
          _command = "7";
          break;
        case 544943:
          _command = "8";
          break;
        case 577583:
          _command = "9";
          break;

        case 538823:
          _command = "RED";
          break;
        case 571463:
          _command = "GREEN";
          break;
        case 546983:
          _command = "YELLOW";
          break;
        case 555143:
          _command = "BLUE";
          break;




        case 554633:
          _command = "TTX";
          break;
        case 562793:
          _command = "TTX_LARGE";
          break;
        case 553613:
          _command = "TTX_CLOSE";
          break;
        case 538313:
          _command = "TTX_PART";
          break;
        case 546473:
          _command = "TTX_HELP";
          break;
        case 566873:
          _command = "G";
          break;

          
        default:
          _code = 0;
          _command = "";
          break;
      }
    }


    
    if (_code != 0)
    {
      if (_code > 33692933 || _code < 0)
        return;
      
      Serial.print("# Remote [");
      Serial.print(_remoteType);
      Serial.print("] Command [");
      Serial.print(_command);
      Serial.print("] Code:");
      Serial.println(_code);
    }
  }

  

public:

  RemoteControls()
  {}


  void UseTypeDefault()
  {
    _remoteType = "DEFAULT";
    Reset();
  }
  
  void UseTypeCarMp3()
  {
    _remoteType = "CARMP3";
    Reset();
  }

  void UseTypeHumax()
  {
    _remoteType = "HUMAX";
    Reset();
  }



  void SetCode(long value)
  {
    setCommand(value);
  }

  void GetCode()
  {
    return _code;
  }
  String GetCommand()
  {
    return _command;
  }

  bool HasCode()
  {
    return (_code != 0);
  }

  bool IsCommand(String value)
  {
    return (_command == value);  
  }

  bool IsCommand(String value1, String value2)
  {
    return (_command == value1 || _command == value2);  
  }

  bool IsCommand(String value1, String value2, String value3)
  {
    return (_command == value1 || _command == value2 || _command == value3);  
  }



  void Reset()
  {
    _code = 0;
    _command = "";
  }

  
};






#endif
