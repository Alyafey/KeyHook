public class GlobalEventListener
{
	PoolHook pt;
	public GlobalEventListener()
	{
		pt = new PoolHook(this);
		pt.start();
			
	}
 
	protected javax.swing.event.EventListenerList listenerList = new javax.swing.event.EventListenerList();
 	
	public void addKeyboardEventListener(KeyboardEventListener listener)
	{
		listenerList.add( KeyboardEventListener.class, listener );
	}
 
	public void removeKeyboardEventListener(KeyboardEventListener listener)
	{
		listenerList.remove( KeyboardEventListener.class, listener );
	}
	
	
	void keyPressed(KeyboardEvent event)
	{
		Object[] listeners = listenerList.getListenerList();
		for ( int i = 0; i < listeners.length; i += 2 )
		{
			if ( listeners[ i ] == KeyboardEventListener.class )
			{
				( (KeyboardEventListener)listeners[i + 1] ).GlobalKeyPressed( event );
			}
		}
	}
 
	void keyReleased(KeyboardEvent event)
	{
		Object[] listeners = listenerList.getListenerList();
		for ( int i = 0; i < listeners.length; i += 2 )
		{
			if ( listeners[ i ] == KeyboardEventListener.class )
			{
				( (KeyboardEventListener)listeners[i + 1] ).GlobalKeyReleased( event );
			}
		}
	}
	
	
}
 

