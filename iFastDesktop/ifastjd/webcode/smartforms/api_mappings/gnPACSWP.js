API.gnPACSWPRequest = {};

API.gnPACSWPRequest = {
	type: 'node'
	,isRequired: function(node){return node.hasData()}
	,description: 'PAC-SWP'
	,repeatCount: 4		
	,contents: {
		PACSWP: {
			type: 'node'
			,isRequired: function(node){return node.hasData()}		
			,contents: {
				accountidtgroup:{
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						accountIDType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'Account'
						}
						,accountIDValue: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'Account'
						}	
					}
				}
				,transType: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return true}				
					,description: 'Trans. Type'
				}	
				,effDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return true}				
					,description: 'Effective Date'
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
					,listName: 'PACSWPFreqCode'
				}
				,dOfWeek: {
					 type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Day of Week'
					,listName: 'dOfWeek'
				}
				,months: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Months'
				}
				,eom: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'End of month'
				}
				,amount: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return true}				
					,description: 'Amount'
				}
				,amtType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return true}				
					,description: 'Amount type'
					,listName: 'SWPamtType'
				}
				,grossNet: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return true}				
					,description: 'Gross-Net'
					,listName: 'grossNetIndicator'
				}
				,adCd: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}					
					,description: 'Address Code for the SWP Cheque'
				}
				,currency: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'currency for PAC/SWP'
				}
				,sourceOfFund: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'source of funds'
				}
				,srcAccount: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'source account'
				}
				,loanNumber: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'loan number'
				}
				,Fee: {
					type: 'node'
					,isRequired: function(){return false}		
					,contents: {
						feeType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'type of fee'
						}
						,amtType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'amount type'
						}
						,feeAmt: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'fee amount percentage'
						}
						,currency: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'currency for the fee'
						}
					}
				}
				,Commission: {
					type: 'node'
					,isRequired: function(){return false}		
					,contents: {
						commType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'Commission Type'
						}
						,commRateType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'Commission Rate Type'
						}
						,CommEntity: {
							type: 'node'
							,isRequired: function(){return true}	
							,description: 'Commission Entity'	
							,contents: {
								commEntityType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Commission Entity Type'
								}
								,commRate: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Commission Rate'
								}
							}
						}
						,currency: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'Currency for the commission'
						}
					}
				}
				,payType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Payment Type'
					,listName: 'DivPayType'
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
						,holder: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Bank Account holder'
						}
						,currency: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Currency'
						}		
					}
				}
				,FundList: {
					type: 'node'
					,isRequired: function(){return true}					
					,contents: {
						FundInfo: {
							type: 'node'
							,isRequired: function(node){return node.hasData()}
							,description: 'Allocation'
							,repeatCount: 6
							,contents: {
								fundIDType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Type of ID for fund identifier'
								}
								,fundIDValue: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'fund identifier value'
								}
								,amtType: {
									type: 'field'						
									,dataType: 'listValue'
									,isRequired: function(){return true}				
									,description: 'Amount Type'
									,listName: 'SWPamtType'
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
			}
		}	
	}
};

