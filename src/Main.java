
public class Main  implements KeyboardEventListener {

    static GlobalEventListener gl;

    public static void main(String[] args) throws Exception  
	{
		Main inst = new Main();
		gl = new GlobalEventListener();
	  	gl.addKeyboardEventListener(inst);
	  	
	}
			
    public void GlobalKeyPressed( KeyboardEvent event )
	{
    	if(event.isKeyUp())
    	{
	    	int key = (int) (long)event.getVirtualKeyCode();
			System.out.println( "The Pressed key is: " + GetKey(key)) ;
    	}
	}

	public void GlobalKeyReleased( KeyboardEvent event )
	{
	
	}

	private String GetKey(int key)
	{

		String result = null;

		switch (key)
		{
		case 0:
			result ="Null";
			break;
		case 8:
			result="Back Space";
			break;
		case 9:
			result="Tap";
			break;
		case 13:
			result="Enter";
			break;
		case 19:
			result="Pause Break";
			break;
		case 20:
			result="CAPSE LOCK";
			break;
		case 27:
			result="Escape";
			break;
		case 32:
			result="Space";
			break;
		case 33:
			result="Page UP";
			break;
		case 34:
			result="Page Down";
			break;
		case 35:
			result="End";
			break;
		case 36:
			result="Home";
			break;
		case 37:
			result="Left";
			break;
		case 38:
			result="Up";
			break;
		case 39:
			result="Right";
			break;
		case 40:
			result="Down";
			break;
		case 44:
			result="PRSTSC SYSRQ";
			break;
		case 45:
			result="INS";
			break;
		case 46:
			result="DEL";
			break;
		case 91:
			result="Windows Key";
			break;
		case 93:
			result="Menu";
			break;
		case 160:
			result="Left Shift";
			break;
		case 161:
			result="Right Shift";
			break;
		case 162:
			result="Left Control";
			break;
		case 163:
			result="Right Control";
			break;
		case 164:
			result="Left Alt";
			break;
		case 165:
			result="Righ Alt";
			break;
		case 186:
			result="Semicolon";
			break;
		case 187:
			result="Plus";
			break;
		case 188:
			result="Comma";
			break;
		case 189:
			result="Minus";
			break;
		case 190:
			result="Period";
			break;
		case 191:
			result="Question";
			break;
		case 192:
			result="Tilde";
			break;
		case 219:
			result="Open Brackets";
			break;
		case 220:
			result="BAck Slash";
			break;
		case 221:
			result="Close Brackets";
			break;
		case 222:
			result="Quotation";
			break;
		default:
			if(key >=48 && key <=90)
			{
				char c=(char)key;
				result=Character.toString(c);
				
			}else if(key >=112 && key <=123)
			{
				int temp =key-63;
				if(temp >=49 && temp <=57){
					result = "F";
					char c=(char)temp;
					result +=Character.toString(c);
				}
				else if( temp >=58 && temp <=71)
				{
					result = "F";
					result += "1";
					char c=(char)(temp-10);
					result +=Character.toString(c);
				}
			}
			else
			{
				result="Undefined";
			}
			break;
		}	

		return result;
	}
	
}
