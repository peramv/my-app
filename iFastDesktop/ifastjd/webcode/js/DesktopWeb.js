/*********************************************************************************************
 * @file	DesktopWeb.js
 * @author  Rod Walker 
 * @desc	Declares DesktopWeb namespace and global parameters, separate to 
 * 			DesktopWeb.Main.js because initialization sequence requirements
 *********************************************************************************************/

Ext.namespace("DesktopWeb");

// DeskopWeb global parameters, initialized in XSL
DesktopWeb._SRC_PATH			= null;
DesktopWeb._SERVLET_PATH 		= null;
DesktopWeb._SCREEN_PARAM_MAP	= null;
DesktopWeb._SCREEN				= null;

// used to communicate with Desktop C++ update 
DesktopWeb._SUCCESS	= 'success';
DesktopWeb._FAIL	= 'fail';

// functions called by Desktop C++ - related to updates & confirmation
function LaunchConfirm()
{		
	return DesktopWeb._SCREEN_CONTROLLER.updatesFlag;
}

function update()
{	
	return DesktopWeb._SCREEN_CONTROLLER.doUpdate();	
}

function getUpdateStatus()
{
	return DesktopWeb._SCREEN_CONTROLLER.updateStatus;
}

function getResult()
{
	if (DesktopWeb._SCREEN_CONTROLLER && DesktopWeb._SCREEN_CONTROLLER.getResult)
	{
		return DesktopWeb._SCREEN_CONTROLLER.getResult();
	}	
}

function getAccountNum()
{
	return DesktopWeb._SCREEN_CONTROLLER.getAccountNum();
}

//For Payment Information Screen
function getTransNum()
{
	return DesktopWeb._SCREEN_CONTROLLER.getTransNum();
}

function getFundCode()
{
	return DesktopWeb._SCREEN_CONTROLLER.getFundCode();
}

function getClassCode()
{
	return DesktopWeb._SCREEN_CONTROLLER.getClassCode();
}

function getTransId()
{
	return DesktopWeb._SCREEN_CONTROLLER.getTransId();
}

