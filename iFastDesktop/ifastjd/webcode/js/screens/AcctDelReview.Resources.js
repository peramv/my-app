/*********************************************************************************************
 * @file	AcctDelReview.Resources.js
 * @author	
 * @desc	Resources JS file for Account Deletion Review screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  09 October 2017 Winnie Cheng P0272876
 *		- General Data Protection Regulation-GDPR, Allowing to change the account attribute
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 322;
	var _layoutWidth = 714;
	
	// ****** fields ******
	var _fields = {
	  currentStateDesc: new DesktopWeb.Controls.Label({
		  itemId: 'currentStateDesc', 
		  fieldLabel: _translationMap['currState'],
		  labelStyle: 'white-space:nowrap;',
		  editable: false,
		  width: 260
	  })
	  ,stateTo: new DesktopWeb.Controls.SMVComboBox({
		  itemId: 'stateTo',
		  fieldLabel: _translationMap["futureState"],
		  labelStyle: 'white-space:nowrap;',
		  disabled: true,	
		  width: 260,
		  listeners:{ 	
			change: function(fld, newValue, oldValue) {
			   _controller.updatesFlag = false;
			  if (oldValue != newValue && newValue != '') {
				_controller.updatesFlag = true;
			  }
			}
		  }
      })
    } // _fields
	
	// **** buttons ****
	var _buttons = {
		saveBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Save']
			,disabled: true		
			,listeners: {
				click: function() {
					if (_fields['stateTo'].getValue().length < 1){
						_fields['stateTo'].markInvalid(_translationMap['FldRequired']);
					} else {
						//confirm update
						DesktopWeb.Util.displayWarning(_translationMap['confirmWarningMsg'], performDelAttrib, Ext.Msg.OKCANCEL);
						//callback function
						function performDelAttrib(confirm){
							if (confirm == 'ok') {
								_controller.updateAcctDelAttribute();
							}
						}
					}
				}
			}
		})
	} // buttons
	
	// **** grids ****
	var _grids = {
		acctDelReview: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 13
			,style: "margin-bottom:5px"
			,autoScroll: true
			,height: _layoutHeight - 90
			,deferRowRender: false
			,store: new Ext.data.XmlStore({
				record: 'AcctDelState'
				,fields: ['delStateCode', 'delStateDesc', 'modUser', 'modDate', 'modTime','modDateTime']
				,listeners: {
					load: function(store, records){
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['DeteleState'], dataIndex: 'delStateDesc', width:350}
					,{header: _translationMap['updateDateTime'], dataIndex: 'modDateTime', width:180}
					,{header: _translationMap['User'], dataIndex: 'modUser', width:150}
				]							
			})
		})
	}// grid
	
	// PUBLIC ITEMS
	return {
		layoutWidth: 	_layoutWidth
		,layoutHeight:	_layoutHeight
		,fields: 		_fields
		,buttons: 		_buttons
		,grids: 		_grids
		
		,layout: new Ext.Container({		
			height: _layoutHeight
			,width: _layoutWidth
			,items: [	
				{
				  layout: 'column',
				  labelWidth: 100,
				  items: [{
					layout: 'form',
					items: [_fields['currentStateDesc']]
				  }]
				},
				{
				  layout: 'column',
				  labelWidth: 100,
				  items: [{						
					layout: 'column',
					items: [{
							layout: 'form'
							,columnWidth: 0.55
							,items: [_fields['stateTo']]
						}
						,{
							columnWidth: 0.20
							,items: [_buttons['saveBtn']]
						}
					]
				  }]
				},
				{
					xtype: 'fieldset'
					,title: _translationMap['AcctDelReviewGridTitle']
					,width: _layoutWidth
					,items: _grids['acctDelReview']
					,style: "padding-top:10px"
				}
			]					
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Close']
				,handler: function(){
					if (_controller.updatesFlag){
						DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
					}else{
						cancelScreen(true);
					}
					
					function cancelScreen(confirm){
						if (confirm) DesktopWeb.Util.cancelScreen();
					}
				}
			})
		]			
	}
}