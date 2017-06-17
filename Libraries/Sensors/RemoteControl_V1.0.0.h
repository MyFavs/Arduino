#ifndef RemoteControl_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define RemoteControl_h


#include <IRremote.h>

class RemoteControl
{
    //IRrecv irrecv(12);

    //decode_results results;

    void CarMP3_Remote()
    {
        switch (Code)
        {
            case 16753245:
                Command = "CH-";
                break;
            case 16736925:
                Command = "CH";
                break;
            case 16769565:
                Command = "CH+";
                break;
            case 16720605:
                Command = "PREV";
                break;
            case 16712445:
                Command = "NXT";
                break;
            case 16761405:
                Command = "PLAY";
                break;
            case 16769055:
                Command = "VOL-";
                break;
            case 16754775:
                Command = "VOL+";
                break;
            case 16748655:
                Command = "EQ";
                break;
            case 16738455:
                Command = "0";
                break;
            case 16724175:
                Command = "1";
                break;
            case 16718055:
                Command = "2";
                break;
            case 16743045:
                Command = "3";
                break;
            case 16716015:
                Command = "4";
                break;
            case 16726215:
                Command = "5";
                break;
            case 16734885:
                Command = "6";
                break;
            case 16728765:
                Command = "7";
                break;
            case 16730805:
                Command = "8";
                break;
            case 16732845:
                Command = "9";
                break;
            case 16750695:
                Command = "100+";
                break;
            case 16756815:
                Command = "200+";
                break;
            default:
                Command = "";
                break;
        }

        if (Command == "")
        {
            Reset();
        }
    }

  public:
    //--setup
    RemoteControl()
    {
        //irrecv.enableIRIn(); // Start the receiver
    }

    //--loop
    void Update()
    {
        // if (irrecv.decode(&results))
        // {
        //     Code = results.value;
        //     CarMP3_Remote();
        //     irrecv.resume(); // Receive the next value
        // }
    }

    void Reset()
    {
        Code = 0;
        Command = "";
    }

    long Code = 0;
    String Command = "";
};

#endif // RemoteControl_h