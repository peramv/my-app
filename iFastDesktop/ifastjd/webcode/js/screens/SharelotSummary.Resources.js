/*********************************************************************************************
 * @file	: SharelotSummary.Resources.js
 * @author	
 * @desc	: Resources file for Sharelot Information screen
 *
 * History  : 21 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54443
 *            - Correct the format of all date fields based on registry edit
 *              ,called displayMark
 *             
 *  07 May 2018 Pao - Supareuk S.
 *  		In goToScreen function, we changed a way to show the page from window.location 
 *  		using buildURL to DesktopWeb.Util.goToScreen. This is to solve an issue when 
 *  		user's profile has too many slot attached. If the session is included, the page
 *  		will be broken as too large.
 *  		- Add a new listener when user clicked on transaction type and it's a valid
 *  		hyper-link to reload the screen with transaction id
 *  
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 680;
	var _layoutWidth = 715;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 30
	});
	
	var _blank = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 30
	});
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({								
		height: 45									
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id);}
		}
	});			
	

	// **** fields ****
	var _fields = {
		fundClass: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['PF_FundClass']
			,width: 200, typeAhead: true 
		})
		,shareLotType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: 'Share Lot Type'
			,width: 150
		})
		,asOfDate: new DesktopWeb.Controls.DateField({
				fieldLabel: 'As Of Date'
				,width: 120
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,activeOnly: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: 'Active Only'
			,width: 120
		})
	
		,selectedTrans_sel: new DesktopWeb.Controls.Radio({
				boxLabel: 'For Selected Transaction'
				,itemId: 'selectedTrans'
				,name: 'selectTrans'
				,disabled:true
				
		})
		,selectedTrans_all:new DesktopWeb.Controls.Radio({
				boxLabel: 'All Transactions'
				,itemId: 'allTrans'
				,name: 'selectTrans'
				,checked: true				
			})	
	
	//Valuation Class enquiry
		,valuDT: new DesktopWeb.Controls.Label({
			fieldLabel: 'Valuation Date'
			,text: ''
	
		})
		,gav: new DesktopWeb.Controls.Label({
			fieldLabel: 'GAV'
			,text: ''

		})
		,nav: new DesktopWeb.Controls.Label({
			fieldLabel: 'NAV'
			,text: ''
	
		})
		,unitBal: new DesktopWeb.Controls.Label({
			fieldLabel: 'Unit Balance'
			,text: ''//replace value
	
		})
		,classValue: new DesktopWeb.Controls.Label({
			fieldLabel: 'Value'
			,text: ''//replace value
	
		})
		,classHWM: new DesktopWeb.Controls.Label({
			fieldLabel: 'Class HWM'
			,text: ''//replace value
	
		})
		,classAdjHWM: new DesktopWeb.Controls.Label({
			fieldLabel: 'Class Adj HWM'
			,text: ''//replace value
	
		})
		//transaction section
		,transType: new DesktopWeb.Controls.Label({
			fieldLabel: 'Trans Type'
			,text: ''
	
		})
		,transNum: new DesktopWeb.Controls.Label({
			fieldLabel: 'Trans Number'
			,text: ''
	
		})
		,tradeDT: new DesktopWeb.Controls.Label({
			fieldLabel: 'Trade Date'
			,text: ''
	
		})
		,units: new DesktopWeb.Controls.Label({
			fieldLabel: 'Units'
			,text: ''
	
		})
			
		,amount: new DesktopWeb.Controls.Label({
			fieldLabel: 'Amount'
			,text: ''
	
		})
		,emptyField: new DesktopWeb.Controls.Label({
			fieldLabel: ''	
			,width: 120
			,text:''																					
		})
		};
	
	
	function renderSimple(value, p, record) {
			return value;
    }
	function renderEQ(value, p, record) {
		if(value == 'EQ Credit'){
			return  '<a href="javascript:DesktopWeb.ScreenController.linkToSelfWithTrans()">' + value + '</a>';
		}else{
			return value;
		}
    }
	
	function renderRedemption(value, p, record) {		
		
		var vLink = value;
		
		if(value == 'Redemption' || value == 'EQ Purchase' ||value == 'EQ Redemption' || value == 'Transfer Out' ||value == 'Exchange Out'){
			var screenname = "SharelotSummary";
			var i, vSplitTxt = "", vParamsStr = "";
			
			if(record.data.linkParams != ""){
				vSplitTxt = record.data.linkParams.split("&");
				for (i = 1; i < vSplitTxt.length; i++) { 
					vParamsStr = vParamsStr + vSplitTxt[i].split("=")[0] + ": '" + vSplitTxt[i].split("=")[1] + "' ,";
				}
				
				/* As of date and active only are not required as existing
				 * User is able to select inactive transaction that belongs to
				 * inactive Lot ID. In this case, we will send blank asOfDate  
				 * and activeOnly fields as existing 
				 */
				vParamsStr = "{" + vParamsStr.substring(0, vParamsStr.length - 1) + ", asOfDate: '', activeOnly: '' }";
				vLink = '<a href="#" onclick="javascript:DesktopWeb.Util.goToScreen(\'' + screenname + '\', ' + vParamsStr + ');">' + value + '</a>';
			}
		}
		
		return vLink;
    }

	// **** grids (tables) ****
	var _grids = {
		shareLotSummary: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth	- 25		
				,autoScroll: true
				,layout: 'fit'							
				,height:  150														
				,store: new Ext.data.XmlStore(
					{
						record: 'Sharelot'					
						,fields: ['originTransType', 'tradeDate', 'origFundUnits', 'unitBalAsofDate', 'valueBalAsOfDate', 'eqPotenValue', 'eqMKTValue','lotID','TransDetls']
						,listeners:{
							load:function(store,records){
								if(store && store.data && store.data.length>0){
									_grids['shareLotSummary'].enableButton('detlBtn');
								}else{
									_grids['shareLotSummary'].disableButton('detlBtn');
								}
								Ext.each(records, function(record){
									record.data.tradeDate = DesktopWeb.Util.getDateDisplayValue(record.data.tradeDate);
								});
								store.fireEvent('datachanged', store); //to set data in grid again
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								_controller.sharelotSelected(record);
							}
							,rowdeselect: function(){
								//_controller.updateActionButtons();
							}
						}												
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [													
							{header: 'Original <br />Trans Type', dataIndex: 'originTransType', width:100, renderer: renderSimple }					            
							,{header: 'Trade Date', dataIndex: 'tradeDate', width:90}
							,{header: 'Original <br />Units', dataIndex: 'origFundUnits', width:90}
							,{header: 'Unit Balance', dataIndex: 'unitBalAsofDate', width:90}
							,{header: 'Value Balance', dataIndex: 'valueBalAsOfDate', width:100}
							,{header: 'Equalisation <br />Potential Value', dataIndex: 'eqPotenValue', width:120}
							,{header: 'Equalisation <br />Market Value', dataIndex: 'eqMKTValue', width:95}
						]							
					}
				)
				,buttons: [					
					new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'detlBtn'
							,text: 'Lots Details by Date'
							
							,handler: function(){_controller.openSharelotDetailsScreen();}
						}
					)										
				]
			}			
		)
		,shareLotDetails: new DesktopWeb.AdvancedControls.GridPanel(
				{							
					width: _layoutWidth	- 25			
					,autoScroll: true						
					,height: 100														
					,store: new Ext.data.XmlStore(
						{
							record: 'TransDetl'					
							,fields: ['transType',{name:'linkParams',mapping:'transType > @parms'}
										,'transnumber','transTypeDesc'
										,'deff', 'settleDate', 'units'
										,'prices', 'tradeAmt', 'eqAmount']							
							,listeners:{
								load:function(store, records){								
									Ext.each(records, function(record){
										record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
										record.data.settleDate = DesktopWeb.Util.getDateDisplayValue(record.data.settleDate);
									});
									store.fireEvent('datachanged', store); //to set data in grid again
								}
							}
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{					
							singleSelect: true
							,listeners: {
								rowselect: function(selModel, index, record){
									
									//_controller.updateActionButtons();
									}
								,rowdeselect: function(){
									
									//_controller.updateActionButtons();
									}
							}												
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [													
								{
								
								header: 'Trans Number', dataIndex: 'transnumber', width:105}
								
								,{header: 'Trans Type', dataIndex: 'transType', width:120, renderer: renderRedemption}
								,{header: 'Trade Date', dataIndex: 'deff', width:120}
								,{header: 'Settle Date', dataIndex: 'settleDate', width:120}
								,{header: 'Units', dataIndex: 'units', width:100}
								,{header: 'EQ Amount', dataIndex: 'eqAmount', width:100}
								//,{header: 'Price', dataIndex: 'prices', width:60}
								//,{header: 'Trade Amount', dataIndex: 'tradeAmt', width:120}
							]							
						}
					)	
				}			
			)				
			
	}
	
	// **** popups ****
	var _popups = {	
										
	} ;
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight

		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight, width: _layoutWidth
			,items: [
				{
					xtype: 'fieldset'
						,title: ""					
						,width: 700
						//,style: "padding-top:10px"
						,items: [
							{
								layout: 'form'														
								,width: 700							
								,items: [
								      _blank
							         ,{
							        	 layout: 'column'						
												,items: [
													{								
														layout: 'form'
														,labelWidth: 100															
														,width: 350	
														,style: "padding-top:5px"
														,items: [
														         
														    _fields['fundClass']
															,_fields['asOfDate']
														]
													}
													
													,{
														layout: 'form'
														,width: 350	
														,style: "padding-top:5px"
														,labelWidth: 100
														,items: [
														    _fields['shareLotType']
															,_fields['activeOnly']
														    ,{
														    	layout: 'column'	
														    	
														    	,items:[
														    	         _fields['selectedTrans_sel']
																		,_fields['selectedTrans_all']
														    	        ]
														    		
														    }
														   
														]
													}
												]
							         }
							     ]
							}
						]
						,buttons: [					
							new DesktopWeb.Controls.ActionButton(		
								{
									itemId: 'addBtn'								
									,text: 'Refresh'							
									//,handler: function(){_controller.openActionPopup(_controller.ADD);}
									,handler: function(){_controller.reloadData();}
								}
							)
																	
						]
				}
				//Class level display
				,{
					layout: 'column'
						,id:'classlevel_fieldset'
						,width: 700							
						,items: [
						        {
						        	 layout: 'form'
						        		 ,width: 250
						        		 ,labelWidth: 100
						        		 ,items:[
							        		     _fields['emptyField']
						        		         ,_fields['valuDT']
						        		         ,_fields['unitBal']
						        		         ,_fields['classAdjHWM']
						        		         
						        		        ]
						         }
						         ,{
						        	 layout: 'form'
						        		 ,width: 225
						        		 ,labelWidth: 70
						        		 ,items:[
						        		         _fields['gav']
						        		         ,_fields['nav']
						        		         ,_fields['classHWM']
						        		         ,_fields['classValue']						        		    
						        		        ]
						         }
						         ,{
						        	 xtype: 'fieldset'
											,title: "Transaction Information"		
											,id:'transInfo_fieldset'			
											,width: 225
											,items: [
														{
														layout: 'form'														
														,width: 200							
														,items:[
										        		         _fields['transType']
										        		         ,_fields['transNum']
										        		         ,_fields['tradeDT']
										        		         ,_fields['units']
										        		         ,_fields['amount']
										        		    
										        		        ]
														}
													]
						         }
					]
				}
				,{
					xtype: 'fieldset'
						,title: "Summary sharelot "					
						,width: 700
						,style: "padding-top:10px"
						,items: [
							{
							layout: 'form'														
							,width: 700							
							,items: _grids['shareLotSummary']
							}
						]
				}
				,{
					xtype: 'fieldset'
						,title: "Transaction associated sharelot"					
						,width: 700
						//,style: "padding-top:10px"
						,items: [
							{
							layout: 'form'														
							,width: 700							
							,items: _grids['shareLotDetails']
							}
						]
				}
			]





																						
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: 'PDF'
					,handler: function(){
						_controller.createPDF();
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'OK' //for inquiry screen OK and Cancel are same 
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'Cancel'
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)

		]			
	}
}