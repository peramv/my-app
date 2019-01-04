/*********************************************************************************************
 * @file	VersionFeatures.Resources.js
 * @author 	Suchit Majumdar
 * @desc	Resources JS file for Version Features screen.
 *
 * History
 * 06 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54444
 *             Correct the format of all date fields based on registry edit
 *             ,called displayMark
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
		var _layoutHeight = 280;
		var _layoutWidth = 700;
	
	// **** fields ****
		var _fields = {			
			accountNumber: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['accountNumber']										
				,width: 100					
			})	
			,contractType: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['contractType']
				,width: 80				
			})
			,versionNumber: new DesktopWeb.Controls.Label({			
				fieldLabel: _translationMap['versionNumber']				
				,width: 80			
			})
			,feature: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['featureSMV']
		})

		}
    
	// **** grids ****
			var _grids =  {
					versionFeatureGrid : new DesktopWeb.AdvancedControls.GridPanel({
					width: _layoutWidth
					,height: 220
					,autoScroll: true
					,style: 'margin-top:20px;margin-left:10px'
					,store: new Ext.data.XmlStore(
						{
							record: 'Mstr'
							,fields: ['cotacctoptionid','feature', 'featureCode', 'option', 'runMode', 'availability','createdOn', 'createdBy','status','userName','processDate','modUser','modDate']
							,listeners: {
								load: function(store, records)
								{
									Ext.each(records, function(record){
										record.data.createdOn = DesktopWeb.Util.getDateDisplayValue(record.data.createdOn);
										record.data.processDate = DesktopWeb.Util.getDateDisplayValue(record.data.processDate);
										record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
									});
									store.fireEvent('datachanged', store); //to set data in grid again
								}
							}
						}
					)
					,selModel: new Ext.grid.RowSelectionModel({
						singleSelect: true

							,listeners: {
								rowselect: function(selModel, index, record){
								_controller.checkModifyButton();
							}
						}
					})

					,colModel: new Ext.grid.ColumnModel({
						defaults: {
							menuDisabled: true
						}

						,columns: [	
							{header: _translationMap['feature'], width: 190, dataIndex: 'feature' ,id: 'feature'},
							{header: _translationMap['option'], width: 100, dataIndex: 'option'}
							,{header: _translationMap['availability'], width: 80, dataIndex: 'availability'},
							{header: _translationMap['createdOn'], width: 80, dataIndex: 'createdOn'},
							{header: _translationMap['createdBy'], width: 80, dataIndex: 'createdBy'},
							{header: _translationMap['status'], width: 155, dataIndex: 'status'}
						]
					})

					,buttons: [
						new DesktopWeb.Controls.ActionButton({
							itemId: 'modBtn'
							,disabled: true
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup(_controller.MOD);}
						})

						,new DesktopWeb.Controls.ActionButton({
							itemId: 'adminBtn'
							,disabled: true
							,text: _translationMap['Admin']
							,handler: function(){_controller.openAdminPopup('');
							}
						})

						,new DesktopWeb.Controls.ActionButton({
							itemId: 'historyBtn'
							,disabled: true
							,text: _translationMap['History']
							,handler: function(){_controller.openHistoricalPopup();
							}
						})

					]

				})
			};	
			
			
	// **** popups ****
		var _popups = {
		versionFeaturePopup: new DesktopWeb.AdvancedControls.PopupWindow({
				width: 600
				,height: 180
				,action: null				
				,modal: true
				,defaults: {border:false}
				,items: [
					{
					html: _translationMap['DeleteConfirmMsg']
					,style: {'text-align':'center','padding-top':'1px'}
					}
					,{
						layout: 'column'
						,style: 'padding:5px'
						,defaults: {border:false}
						,items: [
							{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [
									{
										layout: 'form'
										,defaults: {border:false}
										,items: [
											new DesktopWeb.Controls.SMVComboBox({	
												itemId: 'feature'
												,width: 170
												,fieldLabel: _translationMap['featureSMV']
												,allowBlank: false
											})
										]
									}
									,{
										layout: 'form'
										,defaults: {border:false}
										,items: [
											new DesktopWeb.Controls.SMVComboBox({
												itemId: 'options'
												,width: 170
												,fieldLabel: _translationMap['optionsSMV']
												,allowBlank: false
											})
										]
									}
									,{
										layout: 'form'
										,defaults: {border:false}
										,items: [
												new DesktopWeb.Controls.SMVComboBox({						
												itemId: 'status'
												,width: 170
												,fieldLabel: _translationMap['statusSMV']
												,allowBlank: false
											})
										]
									}

								]
							}
							,{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [
									{
										layout: 'form'
										,defaults: {border:false}
										,items: [
												new DesktopWeb.Controls.SMVComboBox({						
												itemId: 'availability'
												,width: 170
												,fieldLabel: _translationMap['availabilitySMV']
												,allowBlank: false
											})
										]
									}
									,{
										layout: 'form'
										,defaults: {border:false}
										,items: [
												new DesktopWeb.Controls.DateField({						
												itemId: 'createdOn'
												,width: 170
												,fieldLabel: _translationMap['createdOn']
												,allowBlank: false
												,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											})
										]
									}
									,{
										layout: 'form'
										,defaults: {border:false}
										,items: [
												new DesktopWeb.Controls.SMVComboBox({						
												itemId: 'createdBy'
												,width: 170
												,fieldLabel: _translationMap['createdBy']
												,allowBlank: false
											})
										]
									}


								]
							}
								
						]
					}								
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']

					,handler: function(){
						if (_popups['versionFeaturePopup'].isValid()){
							_controller.savePopup(_popups['versionFeaturePopup'].action, _popups['versionFeaturePopup'].getData());
						}	
					}	

				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['versionFeaturePopup'].hide()}
				})
			]
			,init: function(action)	
			{	
				this.action = action					
				this.clearAllFields();
				this.get(0).hide(); //hide delete message
				switch(action)
				{
					case _controller.MOD:
					{
						this.setTitle(_translationMap['versionFeatures'] + ' - ' + _translationMap['Modify']);
						this.getField('feature').disable();
						this.getField('availability').disable();						
						this.getField('createdBy').disable();						
						this.getField('createdOn').disable();
						this.populateWithSelectedRecord();													
					}
				}
			}
			,populateWithSelectedRecord: function(){
				var rec = _grids['versionFeatureGrid'].getSelectedRecord();
				this.getField('feature').setValue(rec.data['feature']);
				this.getField('options').setValue(rec.data['option']);
				this.getField('availability').setValue(rec.data['availability']);
				this.getField('status').setValue(rec.data['status']);
				this.getField('createdBy').setValue(rec.data['createdBy']);
				this.getField('createdOn').setValue(rec.data['createdOn']);


			}

			,getData: function()
			{	
				recordChanged = false;
				var data = {};
				var rec = _grids['versionFeatureGrid'].getSelectedRecord();
				optionOldValue = rec.data['option'];
				optionNewValue = _controller.getListValueDesc('OptionsList', this.getField('options').getValue());
				if((optionNewValue =='') || (optionOldValue == optionNewValue)){
					data['option']=optionOldValue;
				}else{
					data['option']=_controller.getListValueDesc('OptionsList', this.getField('options').getValue());
					recordChanged = true;
				}	
				statusOldValue = rec.data['status'];
				statusNewValue = _controller.getListValueDesc('StatusList', this.getField('status').getValue());
				if((statusNewValue =='') || (statusOldValue == statusNewValue)){
					data['status']=statusOldValue;
				}else{
					data['status']=_controller.getListValueDesc('StatusList', this.getField('status').getValue());
					recordChanged = true;
				}

				if(recordChanged){	
					data['runMode'] = this.action;
				}
				data['feature']=this.getField('feature').getValue();
				data['availability']=this.getField('availability').getValue();
				data['createdBy']=this.getField('createdBy').getValue();
				data['createdOn'] = DesktopWeb.Util.getDateString(this.getField('createdOn').getValue(), DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
				return data;
			}														

		})

		,admin: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 395				
			,closeAction: 'hide'
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					layout: 'column'
					,style: 'padding:4px'
					,defaults: {border: false, labelWidth:80}
					,items: [
						{
							width: 185
							,layout: 'form'
							,defaults: {width:80}
							,items: [
								new DesktopWeb.Controls.Label({
									itemId: 'userName'
									,fieldLabel: _translationMap['Username']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'modUser'
									,fieldLabel: _translationMap['ModUser']
								})
							]
						}
						,{
							width: 185
							,layout: 'form'
							,defaults: {width: 80}
							,items: [
								new DesktopWeb.Controls.Label({
									itemId: 'procDate'
									,fieldLabel: _translationMap['ProcessDate']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'modDate'
									,fieldLabel: _translationMap['ModDate']										
								})
							]
						}
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){_popups['admin'].hide();}
				})
			]
			,init: function(title, data)
			{
				this.setTitle(title);
				this.getField('procDate').setValue(data['procDate']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['userName']);
				this.getField('modUser').setValue(data['modUser']);	
			}
		})
		,history: new DesktopWeb.AdvancedControls.HistoryPopup()


	} 

	//**** buttons ****

	 return {
   		
   		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids

		,popups: _popups
		
		,layout: new Ext.Container(
			{																							
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					{
						layout: 'column'
						,items:[
							{
								layout: 'form'
								,style: 'margin: 10px 0 0 10px'
								,columnWidth: 0.36
								,items:[
									_fields['accountNumber']
								]
							}
							,{
								layout: 'form'
								,style: 'margin-top: 10px'
								,columnWidth: 0.32
								,items:[
									_fields['contractType']
								]
							}
							,{
								layout: 'form'
								,style: 'margin-top: 10px'
								,columnWidth: 0.32
								,items:[
									_fields['versionNumber']
								]
							}
						]
					}
					,{
					items: _grids['versionFeatureGrid']
					}
				]
					
			}
		)
		,screenButtons : [

			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function(){
						DesktopWeb.Util.commitScreen()}
				}
			)
			,new DesktopWeb.Controls.ScreenButton
			(
				{
					text: _translationMap['Cancel']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)							
		]	 			
	} 
	
}

