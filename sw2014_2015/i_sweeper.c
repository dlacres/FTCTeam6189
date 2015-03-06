void SweeperControl(bool SweeperTrue)
{

  if (SweeperTrue==true)
    {
    	servo[sweeper]=200;
    }

  if (SweeperTrue==false)
    {
      servo[sweeper]=127;
    }
  return;
}
