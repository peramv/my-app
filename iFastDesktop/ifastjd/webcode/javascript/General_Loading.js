var intval = "";

function start_Int()
{
  if ( intval=="" )
  {
    intval=window.setInterval("start_clock()",250)
  }
  else
  {
    stop_Int()
  }
}

function stop_Int()
{
  if ( intval != "" )
  {
    window.clearInterval(intval);

    intval="";

    document.getElementById('loadingBar3').style.display='none';
    //document.getElementById('loadingBar3').innerHTML="Interval Stopped"
  }
}

var state = "Loading";

function start_clock()
{
  var d = new Date();

  //var ms=Math.floor(d.getMilliseconds()/100) %4 + "";

  if ( state == "Loading" )
  {
    state = "Loading.";;
  }
  else if ( state=="Loading." )
  {
    state = "Loading..";
  }
  else if ( state=="Loading.." )
  {
    state = "Loading...";
  }
  else
  {
    state = "Loading";
  }

  document.getElementById('loadingBar3').innerHTML= state;
}

function showLoading()
{
  start_Int();
}

function hideLoading()
{
  stop_Int();
}
