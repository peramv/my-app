/*********************************************************************************************
 * @file	AcctStDataVerify.Resources.js
 * @author	
 * @desc	Resources JS file for Account Static Data Verification screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  04 Jan 2018 G. Umamahesh PBSGEALV-135,PBSGEALV-181 & PBSGEALV-177
 *					- Added VerifyCategory,Shareholder Number columns and verification of the Shareholder,Broker,Branch and Sales Rep
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 300;
	var _layoutWidth = 720;
	
	// **** fields ****
	
	// **** buttons ****
		
	var _expander = new Ext.ux.grid.RowExpander({

		expand: false

		,listeners: {
			beforeexpand : function( _expander, record, body, rowIndex) {
				_grids['acctStDataVerifyGrid'].setSelectedRecord(rowIndex)
            }
		}
        ,tpl : new Ext.XTemplate(
        	'<div class="DetailsSectionDiv">'
				,'<table>'
					,'<thead>'
						,'<tr>'
							,'<td style= "width: 100px"><b>{[this.fieldNames("fldLabel")]}</b></td>'
							,'<td style= "width: 100px"><b>{[this.fieldNames("oldVal")]}</b></td>'
							,'<td style= "width: 100px"><b>{[this.fieldNames("newVal")]}</b></td>'
						,'</tr>'
					,'</thead>'
					,'<tbody>'
						,'<tpl for="this.recordList()">'
							,'<tr><td>{.:this.recordListSplit()}</td><td>{.:this.oldValuesSplit()}</td><td>{.:this.newValuesSplit()}</td></tr>'
						,'</tpl>'
					,'</tbody>'
				,'</table>'
			,'</div>'				

			,{
					fieldNames: function(fieldName)
					{
						return _translationMap[fieldName];
					}
					,recordList: function()
					{												
						return _controller.recordsList();
					}
					,recordListSplit: function(str)
					{
						return str.split('~')[0];
					}
					,oldValuesSplit: function(str)
					{
						return str.split('~')[1];
					}
					,newValuesSplit: function(str)
					{
						return str.split('~')[2];
					}

			}	
        )
    });
	
	// **** grids ****
	var _grids = {
		acctStDataVerifyGrid: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth
			,style: "margin-bottom:15px"
			,autoScroll: true
			,height: 250
			,deferRowRender: false
			,store: new Ext.data.XmlStore({
				record: 'EntityInfo'
				,fields: ['entityId']
				,fields: ['ShareHolder','entityId', 'verifyStat', 'modDate', 'modTime', 'modUser', 'verifyDate', 'verfyUser', 'fldLabel', 'oldVal', 'newVal','VerifyCategory','VerifyRequestUUID']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
							record.data.verifyDate = DesktopWeb.Util.getDateDisplayValue(record.data.verifyDate);
							record.data.taintendDt = DesktopWeb.Util.getDateDisplayValue(record.data.taintendDt);									
						});

						store.fireEvent('datachanged', store); //to set data in grid again
						
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true

				,listeners: {
					rowselect: function(selModel, index, record){
						_controller.checkVerifyButton();
					}
				}

			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					_expander
					,{header: _translationMap['ShareHolder'], dataIndex: 'ShareHolder', width:100}
					,{header: _translationMap['VerifyCategory'], dataIndex: 'VerifyCategory', width:100}
					,{header: _translationMap['verifyStat'], dataIndex: 'verifyStat', width:100}
					,{header: _translationMap['entityId'], dataIndex: 'entityId', width:70}
					,{header: _translationMap['modDate'], dataIndex: 'modDate', width:100}
					,{header: _translationMap['modTime'], dataIndex: 'modTime', width:100}
					,{header: _translationMap['modUser'], dataIndex: 'modUser', width:100}
					,{header: _translationMap['verifyDate'], dataIndex: 'verifyDate', width:100}
					,{header: _translationMap['verfyUser'], dataIndex: 'verfyUser', width:100}
				]							
			})
			,plugins: _expander
		})
	}
	
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,expander: _expander
	
		,grids: _grids
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [	
					{
						layout: 'column'						
					}
					,_grids['acctStDataVerifyGrid']
				]					
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					id: 'verifyButton'
					,disabled: true
					,text: _translationMap['verify']
					,handler: function(){
						_controller.verifyStaticDataChanges();
					}
				}
			)


			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}