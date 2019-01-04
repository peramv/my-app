/*********************************************************************************************
 * @file	ClassSetup_ValuationBasic.Resources.js
 * @author	Cherdsak Sangkasen
 * @desc	Resources JS file for Valuation Detail screen	
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54443
 *          - Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 725;
	var _layoutWidth = 715;
	
	// **** fields ****
	var _fields = {		
		dtpValnDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['ValuationDate']
				, width: (_layoutWidth / 4) - 20
				, height: 20
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
				, listeners:{          
					change: function() {
						_controller.doReload();	
					}
				}
			}
		)
		, lblCrysFlag: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['CrystalisationDate']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, crysFlag: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblDistFlag: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['DistributionDate']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, distFlag: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblGav: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['Gav']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, gav: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblDivAdjGav: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['DivAdjGav']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, divAdjGav: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblDistRate: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['DistRate']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, distRate: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblNav: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['Nav']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, nav: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblCalcBasis: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['CalcBasis']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, calcBasis: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblPfPerShare: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['PfPerShare']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, pfPerShare: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblLossCarrFwOptn: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['LossCarrFwOptn']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lossCarrFwOptn: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblClsHWM: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ClsHWM']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, clsHWM: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblClsHWM: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ClsHWM']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, clsHWM: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblDivTreatOptn: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['DivTreatOptn']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, divTreatOptn: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblClsHWMDate: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ClsHWMDate']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, clsHWMDate: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblCalcPrec: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['CalcPrec']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, calcPrec: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblNumDays: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['NumDays']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, numDays: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblPfPrec: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['PfPrec']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, pfPrec: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblPfPrec: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['PfPrec']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, pfPrec: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblEffHurdle: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['EffHurdle']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, effHurdle: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblValStatus: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['Status']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, valStatus: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblClsAdjHWM: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ClsAdjHWM']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, clsAdjHWM: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 10
				, height: 20
			}
		)
		, lblNewClsHWM: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['NewClsHWM']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 60
				, height: 20
			}
		)
		, newClsHWM: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 80
				, height: 20
			}
		)
		, lblValEqCr: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ValEqCr']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 60
				, height: 20
			}
		)
		, valEqCr: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 80
				, height: 20
			}
		)
		, lblValEqRed: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ValEqRed']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 60
				, height: 20
			}
		)
		, valEqRed: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 80
				, height: 20
			}
		)
		, lblTotEqPurTxn: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['TotEqPurTxn']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 60
				, height: 20
			}
		)
		, totEqPurTxn: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 80
				, height: 20
			}
		)
		, lblTotEqRedTxn: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['TotEqRedTxn']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 60
				, height: 20
			}
		)
		, totEqRedTxn: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 80
				, height: 20
			}
		)
		, lblTotPfAmt: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['TotPfAmt']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 60
				, height: 20
			}
		)
		, totPfAmt: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 80
				, height: 20
			}
		)
		, lblCrysStatus: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['Status']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 60
				, height: 20
			}
		)
		, crysStatus: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 80
				, height: 20
			}
		)
		, txtValnDate : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['ValuationDate']
				, width: 200
				, labelWidth: 150
			}
		)
		, txtCrysFlag : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['CrystalisationDate']
				, width: 200
				, labelWidth: 150
			}
		)
		, txtDistFlag : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['DistributionDate']
				, width: 200
				, labelWidth: 150
			}
		)
		, txtStatus : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['Status']
				, width: 200
				, labelWidth: 150
			}
		)
		, txtNewHWM : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['NewHWM']
				, width: 200
				, labelWidth: 150
				, maskRe: /[0-9.-]/
			}
		)
		, header : new DesktopWeb.Controls.Label(
			{		
				text: _translationMap['ValuationDetails']
				, style: 'font-weight: bold; font-size: 13px; padding-bottom: 8px;'
			}
		)
	}
	
	// **** buttons **** //
	var _buttons = {
		cmdCancelValn: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['CancelValn']
				, id: 'cmdValnCancel'
				, width: 120
				, handler: function(){ _controller.openActionPopup('frmProcCancel', 'CancelValn'); }							
			}
		)
		, cmdCancelCrys: new DesktopWeb.Controls.ActionButton(
			{
				text:  _translationMap['CancelCrys']
				, id: 'cmdCrysCancel'
				, width: 120
				, handler: function(){ _controller.openActionPopup('frmProcCancel', 'CancelCrys'); }		
			}
		)
		, cmdUserDefHWM: new DesktopWeb.Controls.ActionButton(
			{
				text:  _translationMap['UserDefHWM']
				, id: 'cmdUserDefHWM'
				, width: 120
				, handler: function(){ _controller.openActionPopup('frmNewHWM', 'UserDefHWM'); }						
			}
		)
		, cmdProcSubmit: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Ok']
				, handler: function(){
					if (_popups['frmProcCancel'].isValid())
					{						
						_controller.doProcess(_popups['frmProcCancel'].getData());
					}
				}						
			}
		)
		, cmdProcCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					if (_popups['frmProcCancel'].isValid())
					{
						_popups['frmProcCancel'].hide();
					}
				}						
			}
		)
		, cmdNewHWMSubmit: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Ok']
				, handler: function(){
					if (_popups['frmNewHWM'].isValid())
					{						
						_controller.doProcess(_popups['frmNewHWM'].getData());
					}
				}						
			}
		)
		, cmdNewHWMCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					if (_popups['frmNewHWM'].isValid())
					{
						_popups['frmNewHWM'].hide();
					}
				}						
			}
		)
	}
	
	// **** grids ****
	var _grids = {
		grdHurdle: new DesktopWeb.AdvancedControls.GridPanel
		(
			{
				width: _layoutWidth - 25
				, style: "margin-bottom:15px"
				, autoScroll: true
				, height: 100
				, disableSelection: true
				, store: new Ext.data.XmlStore
				(
					{
						record: 'Hurdle'
						, fields: ['index', 
									'fixRate',
									'benchmark',
									'weighting',
									'period',
									'numDays',
									'dayBasis']					
					}				
				)			
				, colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [	
							{header: 'Fix/Index', dataIndex: 'index', width:60}
							, {header: 'Fix Rate/Hurdle', dataIndex: 'fixRate', width:90, renderer: function(val) {return (val ? val + "%" : ''); }}
							, {header: 'Benchmark/Adjustment ', dataIndex: 'benchmark', width:130, renderer: function(val) {return (val ? val + "%" : ''); }}
							, {header: 'Weighting', dataIndex: 'weighting', width:70, renderer: function(val) {return (val ? val + "%" : ''); }}
							, {header: 'Period', dataIndex: 'period', width:160}
							, {header: 'Number of Days', dataIndex: 'numDays', width:90}
							, {header: 'Day Basis', dataIndex: 'dayBasis', width:80}
						]
					}
				)				
			}		
		)
	}
	
	// **** popups ****
	var _popups = {		
		frmProcCancel: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				, proc: null
				, dummy: ""
				, width: 600
				, closeAction: 'hide'
				, modal: true
				, defaults: {border:false}
				, items: [
					{
						layout: 'form'
						, defaults: {border: false, labelWidth:50}
						, items: [
							{
								layout: 'column'								
								, style: 'padding:4px'
								, defaults: {border: false}
								,items: [ 
									{
										width: 500
										, layout: 'form'
										, labelWidth: 180
										, defaults: {border: false}
										, items: [ 
											_fields['txtValnDate'] 
											, _fields['txtCrysFlag'] 
											, _fields['txtDistFlag'] 
											, _fields['txtStatus']
										]
									}
								]
							}
						]
					}
				]
				, buttons: [
					_buttons['cmdProcSubmit']
					, _buttons['cmdProcCancel']				
				]
				, init: function(proc)
				{					
					this.proc = proc;
					this.disableAllFields();
					this.setTitle(_translationMap[proc]);
					_controller.populateProcess(proc);
				}
				, getData: function()
				{
					var data = {};
					data["proc"] = this.proc;
					data["newClsHWM"] = "";				
					return data;
				}
				, disableAllFields: function()
				{
					_fields['txtValnDate'].disableField();
					_fields['txtCrysFlag'].disableField();
					_fields['txtDistFlag'].disableField();
					_fields['txtStatus'].disableField();
				}
			}		
		)
		, frmNewHWM: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				proc: null
				, width: 600
				, closeAction: 'hide'
				, modal: true
				, defaults: {border:false}
				, items: [
					{
						layout: 'form'
						, defaults: {border: false, labelWidth:50}
						, items: [
							{
								layout: 'column'								
								, style: 'padding:4px'
								, defaults: {border: false}
								,items: [ 
									{
										width: 500
										, layout: 'form'
										, labelWidth: 180
										, defaults: {border: false}
										, items: [ 
											_fields['txtNewHWM'] 
										]
									}
								]
							}
						]
					}
				]
				, buttons: [
					_buttons['cmdNewHWMSubmit']
					, _buttons['cmdNewHWMCancel']				
				]
				, init: function(proc)
				{					
					this.proc = proc;
					this.setTitle(_translationMap['UserDefHWM']);
					_controller.populateNewHWN();
				}
				, getData: function(proc)
				{
					var data = {};
					data["proc"] = this.proc;
					data["newClsHWM"] = _fields['txtNewHWM'].getValue();;				
					return data;
				}			
			}		
		)		
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,buttons: _buttons
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,layout: 'form'
				,items: [
					{
						layout: 'column'
						,items: [
							{
								width: _layoutWidth
								, style: 'text-align:center;margin-bottom:10px;'
								, layout: 'form'
								, items: [
									_fields['header']
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 80}	
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, labelWidth: (_layoutWidth / 4) - 20
								, items: [
									_fields['dtpValnDate']
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblCrysFlag']
											, _fields['crysFlag']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblGav']
											, _fields['gav']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblDistFlag']
											, _fields['distFlag']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblDivAdjGav']
											, _fields['divAdjGav']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblDistRate']
											, _fields['distRate']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblNav']
											, _fields['nav']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblCalcBasis']
											, _fields['calcBasis']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblPfPerShare']
											, _fields['pfPerShare']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblLossCarrFwOptn']
											, _fields['lossCarrFwOptn']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblClsHWM']
											, _fields['clsHWM']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblDivTreatOptn']
											, _fields['divTreatOptn']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblClsHWMDate']
											, _fields['clsHWMDate']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblCalcPrec']
											, _fields['calcPrec']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblNumDays']
											, _fields['numDays']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblPfPrec']
											, _fields['pfPrec']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblEffHurdle']
											, _fields['effHurdle']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblValStatus']
											, _fields['valStatus']
										]
									}
								]
							}
						]
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, items: [
											_fields['lblClsAdjHWM']
											, _fields['clsAdjHWM']
										]
									}
								]
							}
							, {
								width: _layoutWidth / 2
								, layout: 'form'
								, items: [
									{
										width: _layoutWidth / 2
										, layout: 'form'
										, style: 'text-align:right'
										, items: [
											_buttons['cmdCancelValn']
										]
									}
								]
							}
						]
					}
					, {
						xtype: 'fieldset'
						, width: _layoutWidth
						, style: 'position:relative; margin-left:0px; padding-left:10px;'
						, id: 'hurdle_fieldset'	
						, title: _translationMap['HurdleDetl']								
						, items: [
							{							
								layout: 'form'
								,items: [
									_grids['grdHurdle']
								]
							}
						]
					}
					, {
						xtype: 'fieldset'
						, style: 'position:relative; margin-left:0px; padding-left:10px;'
						, id: 'crystalisation_fieldset'	
						, title: _translationMap['CrystalisationDetl']								
						, hideMode: 'offsets'
						, hidden: false
						, width: _layoutWidth
						, items: [
							{
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblNewClsHWM']
													, _fields['newClsHWM']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblTotEqPurTxn']
													, _fields['totEqPurTxn']
												]
											}
										]
									}
								]
							}
							, {
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValEqCr']
													, _fields['valEqCr']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblTotEqRedTxn']
													, _fields['totEqRedTxn']
												]
											}
										]
									}
								]
							}
							, {
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValEqRed']
													, _fields['valEqRed']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblTotPfAmt']
													, _fields['totPfAmt']
												]
											}
										]
									}
								]
							}
							, {
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblCrysStatus']
													, _fields['crysStatus']
												]
											}
										]
									}
								]
							}
						]
						, buttons: [
							_buttons['cmdUserDefHWM']
							, _buttons['cmdCancelCrys']				
						]
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: 'Export PDF'
					,handler: function(){ _controller.exportPDF(); }
				}
			)
			, new DesktopWeb.Controls.ScreenButton(
				{
					text: 'OK'
					,handler: function(){ _controller.goEventMain(); }
					
				}
			)
		]			
	}
}