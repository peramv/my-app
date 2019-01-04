/*********************************************************************************************
 * @file	
 * @author	
 * @desc	
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	
	// content dimensions
	var _layoutHeight = 530;
	var _layoutWidth = 715;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 30
	})
	
	var _blank = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 30
	})
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({								
		height: 45									
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id)}
		}
	})			
	

	//Alert("Are you sure you want to delete the record?")

	//var _toolTipLinkStyle='a:link {text-decoration: underline overline; color: blue; cursor: hand}';
	var _toolTipLinkStyle='';//'a:link {text-decoration: underline overline; color: blue;}; cursor: hand';
	// **** fields ****
	var _fields = {
		valuationDT: new DesktopWeb.Controls.Label({
				fieldLabel: 'Valuation Date'
				//,disabled:true
				,width: 120
				,text: ''
		})
		,transType: new DesktopWeb.Controls.Label({
				fieldLabel: 'Trans Type'
				,width: 120
				,text: ''
		})
		,transNum: new DesktopWeb.Controls.Label({
				fieldLabel: 'Trans Number'
				,width: 120
				,text: ''
		})
		,tradeDT: new DesktopWeb.Controls.Label({
			fieldLabel: 'Trade Date'								
			,width: 120
			,text: ''																					
		})
		,oriGAV: new DesktopWeb.Controls.Label({
				fieldLabel: 'Original GAV'
				,width: 120
				,text: ''
		})
		,origUnits: new DesktopWeb.Controls.Label({
				fieldLabel: 'Original Units'
				,width: 120
				,text: ''
		})
		,change: new DesktopWeb.Controls.Label({
			fieldLabel: 'Change'
			,width: 120
			,text: ''
		})
		,unitBal: new DesktopWeb.Controls.Label({
			fieldLabel: 'Opening Unit Balance'
			,width: 120
			,text: ''
		})
	
	,closingBal: new DesktopWeb.Controls.Label({
		fieldLabel: 'Closing Unit Balance'
		,width: 120
		,text: ''
	})
	
		,lotHWM: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot HWM'
			,width: 120
			,style: 'a:link {text-decoration: underline overline; color: blue;}'
				,text: ''
				,width: 120
				
		})
		,lotHWMDT: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot HWM Date'
			,width: 120
			,text: ''
		})
		,numOfDays: new DesktopWeb.Controls.Label({
			fieldLabel: 'Number of Days since HWM'
			,width: 80
			,text: ''
			})
		,lotEffHurd: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot Effective Hurdle'
				,width: 120
				,style: 'a:link {text-decoration: underline overline; color: blue;}'
					,text: ''
					,width: 120
					
			})
		,lotAdjHWM: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot Adj HWM'
				,width: 120
				,style: 'a:link {text-decoration: underline overline; color: blue;}'
					,text: ''
					,width: 120
					
		})

		//Class section
		,classGAV: new DesktopWeb.Controls.Label({
				fieldLabel: 'GAV'
				,width: 120
				,text: ''
		})
		,classNAV: new DesktopWeb.Controls.Label({
				fieldLabel: 'NAV'
				,width: 120
				,text: ''
		})
		,pfPerShare: new DesktopWeb.Controls.Label({
			fieldLabel: 'Performance Per Share'								
			,width: 120
			,text: ''	
																											
		})
		
		
		
		//field with label
		,lotDetlHeader: new DesktopWeb.Controls.Label({
			fieldLabel: ''
			,width: 250
			,style: "padding-left:160px;padding-top:5px;font-weight: bold; font-size: 11px;&nbsp;"
			,text: "Per Share"
		})
	
		//empty
		,lotDetlHeader2: new DesktopWeb.Controls.Label({
			fieldLabel: ''
				,width: 200
				,style: "padding-left:10px;padding-top:5px;font-weight: bold; font-size: 11px;&nbsp;"
				,text: "Total"
		})
					
		,lotTotPF: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot Total PF Payable'								
			,width: 80
			,emptyText: ""																								
		})
		,lotClassPF: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot Class PF'								
					,style: 'a:link {text-decoration: underline overline; color: blue;}'
						,text: ''
						,width: 120
																											
		})
		,lotEQmv: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot EQmv'								
				,style: 'a:link {text-decoration: underline overline; color: blue;}'
					,text: ''
					,width: 120
																									
		})
		,lotEQpot: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot EQpot'								
				,style:  'a:link {text-decoration: underline overline; color: blue;}'
					,text: ''
					,width: 120
																										
		})
		,lossCarFwd: new DesktopWeb.Controls.Label({
			fieldLabel: 'EQ Lost/Carry Forward'								
			,style:  'a:link {text-decoration: underline overline; color: blue;}'
			,width: 120
			,text: ''																								
		})
		,lotPFFee: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot Performance Fee'	
				,style: 'a:link {text-decoration: underline overline; color: blue;}'
					,text: ''
					,width: 120
			
																											
		})
		,lotShrVal: new DesktopWeb.Controls.Label({
			fieldLabel: 'Lot Share Value'								
				,style: "padding-top:2px"
				,style: 'a:link {text-decoration: underline overline; color: blue;}'
					,text: ''
					,width: 85																														
		})
		,lotVal: new DesktopWeb.Controls.Label({
			fieldLabel: 'Total Lot Value'
				,style: "padding-top:2px"								
				,style: 'a:link {text-decoration: underline overline; color: blue;}'
					,text: ''
					,width: 85
																												
		})

		//fields no label
		,pfTotalPayable: new DesktopWeb.Controls.Label({
			fieldLabel: ''								
				,style: 'padding-top:5px;padding-bottom:10px;padding-left:10px; a:link {text-decoration: underline overline; color: blue;};font-size: 12px;'
					,text: ''
					,width: 120
																													
		})
		
		,emptyField: new DesktopWeb.Controls.Label({
			fieldLabel: ''	
			,width: 120
			,text:''																					
		})
	
		,lotEQmvTotal: new DesktopWeb.Controls.Label({
			fieldLabel: ''
				,style: 'padding-top:5px;padding-bottom:15px;padding-left:10px; a:link {text-decoration: underline overline; color: blue;};font-size: 12px;'
					,text: ''
					,width: 120
																											
		})
		
		,lotClassPFTotal: new DesktopWeb.Controls.Label({
			fieldLabel: ''								
					//,style: 'a:link {text-decoration: underline overline; color: blue;}'
					,style: 'padding-top:5px;padding-bottom:15px;padding-left:10px; a:link {text-decoration: underline overline; color: blue;};font-size: 12px;'
						,text: ''
						,width: 120
																											
		})

		
		,lotEQpotTotal: new DesktopWeb.Controls.Label({
			fieldLabel: ''
				,style: 'padding-top:5px;padding-bottom:15px;padding-left:10px; a:link {text-decoration: underline overline; color: blue;};font-size: 12px;'
					,text: ''
					,width: 120
																													
		})
	
		,lossCryFwdTotal: new DesktopWeb.Controls.Label({
			fieldLabel: ''
				,style: 'padding-top:5px;padding-bottom:15px;padding-left:10px; a:link {text-decoration: underline overline; color: blue;};font-size: 12px;'
					,text: ''
					,width: 120
																												
		})
	
		//left column at bottom
		,transitionType: new DesktopWeb.Controls.Label({
			fieldLabel: 'Transition Type'
			,left: 120
			,text: ''
		
		})
		,transNumber: new DesktopWeb.Controls.Label({
			fieldLabel: 'Transnumber'
			,left: 120
			,text: ''
		
		})
		,NAV: new DesktopWeb.Controls.Label({
			fieldLabel: 'NAV'
			,left: 120
			,text: ''
		
		})
		,numOfUnit: new DesktopWeb.Controls.Label({
			fieldLabel: 'Number of Units'
			,left: 120
			,text: ''
		
		})
		,eqAmount: new DesktopWeb.Controls.Label({
			fieldLabel: 'Equalisation Amount'
			,left: 120
			,text: ''
		
		})
		,newLotHWM: new DesktopWeb.Controls.Label({
			fieldLabel: 'New Lot HWM'
				,style: 'a:link {text-decoration: underline overline; color: blue;};font-size: 12px;'
					,text: ''
					,width: 120
							
		
		})
		//right column at bottom
		,newLotBalance: new DesktopWeb.Controls.Label({
			fieldLabel: 'New Lot Balance'
			,left: 120
			,text: ''
		
		})
	}
	
	// **** grids ****
	var _grids = {
					
				
	}
	
	// **** popups ****
	var _popups = {
									
	} 
	
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
				layout: 'column'						
					,items: [
						{								
							layout: 'form'
							,labelWidth: 150															
							,width: 300		
							,style: "padding-top:10px"
							,items: [
								_fields['valuationDT']
								,_fields['transType']
								,_fields['transNum']
								,_fields['tradeDT']
								//,_fields['oriGAV']
								,_fields['origUnits']	
								,_fields['change']	
								,_fields['unitBal']	
								,_fields['closingBal']	
								,_fields['lotHWM']
								,_fields['lotHWMDT']
								,_fields['numOfDays']
								,_fields['lotEffHurd']
								,_fields['lotAdjHWM']
						         
							]
						}
						,{
							layout: 'form'
							,width: 400	
							,style: "padding-top:10px"
							,items: [
							         {
							        	 xtype: 'fieldset'
												,title: "Class Level Values (Pre PF Crystalisation)"					
												,width: 400
												,style: "padding-top:10px"
												,items: [
												    {
														layout: 'column'														
															,width: 400							
															,items: [
																{
																	layout: 'form'														
																	,width: 400	
																	,labelWidth: 150
																	,items: [
																	         _fields['classGAV']
																	         ,_fields['classNAV']
																	         ,_fields['pfPerShare']
																	]
																}
																
															]
													    
													}
												]
							         }
							         ,{
							         	xtype: 'fieldset'
							        	 ,layout: 'table'
							        	 	,layoutConfig:{columns:2,tableAttrs: {border:'0' } }
							        		,width: 400
											,items: [
												{layout: 'form',width: 300,labelWidth: 150,items:_fields['lotDetlHeader']}
												,_fields['lotDetlHeader2']
												
												,{layout: 'form',width: 300,labelWidth: 150,items:_fields['lotTotPF']}
												,_fields['pfTotalPayable']
												
										        ,{layout: 'form',width: 300,labelWidth: 150,items:_fields['lotClassPF']}
										        ,{layout: 'form',items:_fields['lotClassPFTotal']} 
										         
										        ,{layout: 'form',width: 300,labelWidth: 150,items:_fields['lotEQmv']}
										        ,_fields['lotEQmvTotal']
										         
										        ,{layout: 'form',width: 300,labelWidth: 150,items:_fields['lotEQpot']}
										        ,_fields['lotEQpotTotal']
										         
										        ,{layout: 'form',width: 300,labelWidth: 150,items:_fields['lossCarFwd']}
										        ,_fields['lossCryFwdTotal']
										         
										        ,{layout: 'form',width: 300,labelWidth: 150,items:_fields['lotPFFee']}
										        ,{layout: 'form',items:_fields['emptyField']}
										         
											]
										}
									,{
									xtype: 'fieldset',columnWidth: 0.5
									,layout: 'table'
									,items:[
											{layout: 'form',labelWidth: 100,items:_fields['lotShrVal']}
											,{layout: 'form',labelWidth: 100,items:_fields['lotVal']}
									]
									}
							]
						}
					]
				}
				,{
					xtype: 'fieldset'
						,title: "PF Crystalisation Information"
						,id:'PFCrystInfo_fieldset'					
						,width: 700
						,style: "padding-top:10px"
						,items: [
						    {
								layout: 'column'														
									,width: 700							
									,items: [
										{
											layout: 'form'		
											,labelWidth: 150
											,width: 400							
											,items: [
											         _fields['eqAmount']
											         ,_fields['transitionType']
											         ,_fields['NAV']
											        

											]
										}
										,{
											layout: 'form'														
												,width: 300							
												,items: [
												        _fields['newLotHWM']
												        ,_fields['transNumber']
												        ,_fields['numOfUnit']
												        
												]
										}
									]
							    
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
			/*					
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'OK'
					,handler: function(){
						//DesktopWeb.Util.commitScreen()
						
						var asOfDate = _fields['valuationDT'].getValue().format("m/d/Y");
						_controller.loadInitData(asOfDate);
						}
				}
			)			
			*/
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'Cancel'
					,handler: function(){
								_controller.loadSharelotSummary();
							}
				}
			)
			
		]			
	}
}