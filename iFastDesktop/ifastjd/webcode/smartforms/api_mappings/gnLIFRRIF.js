API.gnLIFRRIFRequest = {};

API.gnLIFRRIFRequest = {
	type: 'node'
	,isRequired: function(node){return node.hasData()}
	,description: 'LIF-RRIF'
	,repeatCount: 2	
	,contents: {
		LIFRRIF: {
			type: 'node'
			,isRequired: function(){return false}		
			,contents: {
				effDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return true}				
					,description: 'Effective Date'
				}
				,origPlanDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return false}				
					,description: 'Original plan Effective Date'
				}
				,stopDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return false}				
					,description: 'Stop Date'
				}
				,freqCode: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return true}				
					,description: 'Frequency'
					,listName: 'LIFRRIFFreqCode'
				}
				,months: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Monthly Indicator as per Frequency Code'
				}
				,eom: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'End of Month Flag'
				}
				,Qualified: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Qualified Flag Default is “No”'
				}
				,payOption: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return true}				
					,description: 'Pay Option Code'
					,listName: 'LIFRRIFpayOption'
				}
				,payType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return true}				
					,description: 'Payment Type'	
					,listName: 'LIFRRIFpayType'				
				}
				,chqAddCde: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Addres Code in iFAST'
				}
				,tRFAcct: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Transfer To Account Number'
				}
				,grossNet: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Gross-Net'
					,listName: 'grossNetIndicator'
				}
				,payAmount: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Payment Amount'
				}
				,indexRate: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Index Rate when Pay Option is Indexed'
				}
				,spsBirthDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return false}				
					,description: 'Spouse Birth Date'
				}
				,taxOnMin: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return true}				
					,description: 'Tax on Minimum Flag'
				}
				,ovAnnualAmt: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Override Annual Amount Flag'
				}
				,ovUnuMax: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Override Unused Maximum Amount Flag'
				}
				,suppFedTax: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Suppress Federal Tax Flag'
				}
				,fedRate: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Federal Tax Rate '
				}
				,fedTaxType: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Federal Tax Rate Type'
				}
				,suppProvTax: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Suppress Provincial Tax Flag'
				}
				,provRate: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Provincial Tax Rate'
				}
				,provTaxType: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Provincial Tax Rate Type'
				}
				,accountidtgroup: {
					type: 'node'
					,isRequired: function(){return false}		
					,contents: {
						accountIDType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'Account Type Always "IFAST"'
						}
						,accountIDValue: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'IFAST Account Number'
						}
					}
				}
				,dOfWeek: {
					 type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Day of the Week'
					,listName: 'dOfWeek'
				}
				,amtType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return true}				
					,description: 'amount type'
					,listName: 'LIFRRIFamtType'
				}
				,amount: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return true}				
					,description: 'amount'
				}
				,sourceOfFund: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Source of Funds'
				}
				,FundList: {
					type: 'node'
					,isRequired: function(){return true}					
					,contents: {
						FundInfo: {
							type: 'node'
							,isRequired: function(){return true}
							,repeatCount: 6
							,contents: {
								fundIDType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Fund ID Type'
								}
								,fundIDValue: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Fund ID Value'
								}
								,amtType: {
									type: 'field'						
									,dataType: 'listValue'
									,isRequired: function(){return true}
									,description: 'Type of Amount'
									,listName: 'LIFRRIFamtType'
								}
								,amount: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Amount'
								}
							}
						}
					}
				}
				,FundListTo: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						FundInfo: {
							type: 'node'
							,isRequired: function(){return true}
							,contents: {
								fundIDType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Fund ID Type'
								}
								,fundIDValue: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Fund ID Value'
								}
								,amtType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Type of Amount'
								}
								,amount: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Percentage allocated to FundIDValue'
								}
							}
						}
					}
				}
				,BkInfo: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						instCode: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Institution code'
						}
						,transitNo: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Transit number'
						}
						,bkAcctType: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Bank account type'
						}
						,bkAcctNum: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Bank account number'
						}
						,currency: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Currency'
								}
						,holder: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Bank Account holder'
						}		
					}
				}
			}
		}		
	}
};