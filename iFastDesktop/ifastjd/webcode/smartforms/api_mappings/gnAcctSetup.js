API.gnAcctSetupRequest = {};

var _gnAcctSetup_clientInfo = {
	type: 'node'
	,isRequired: function(node){return true}	
	,contents: {
		Individual: {
			type: 'node'
			,isRequired: function(node){return node.parentNode.getNodeValue('Org.orgName') == null}			
			,contents: {
				titleCode: {
				 	type: 'field'
				 	,dataType: 'listValue'
					,isRequired: function(){return false}
					,description: 'Title code'
					,listName: 'titleCode'																
				}
				,firstName: {
				 	type: 'field'
				 	,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'First name'																
				}
				,lastName: {
				 	type: 'field'
				 	,dataType: 'string'
					,isRequired: function(node){return true}
					,description: 'Last name'																
				}
				,SIN: {
				 	type: 'field'
				 	,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'SIN'																
				}
				,birthDate: {
				 	type: 'field'
				 	,dataType: 'date'
					,isRequired: function(node){return false}
					,description: 'Birthdate'																
				}
				,gender: {
				 	type: 'field'
				 	,dataType: 'listValue'
					,isRequired: function(){return false}
					,description: 'Gender'
					,listName: 'gender'																
				}
			}
		}
		,Org: {
			type: 'node'
			,isRequired: function(node){return node.hasData()}
			,contents: {
				orgName: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return true}
					,description: 'Organization Name'					
				}
				,fedBN: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Bus. No.'
				}
			}
		}
		,Identification: {
			type: 'node'
			,isRequired: function(){return false}			
			,contents: {
				IDVerify: {
					type: 'node'
					,isRequired: function(){return true}
					,description: 'ID Verify'
					,contents: {
						IDType: {
							type: 'field'
							,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'ID Type'
							,listName: 'AcctSetupIDType'
						}
						,IDNum: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'ID Num'					
						}
						,IDDate: {
							type: 'field'
							,dataType: 'date'
							,isRequired: function(){return false}
							,description: 'ID Date'					
						}
						,PlaceIssue: {
							type: 'node'							
							,isRequired: function(){return false}
							,description: 'Place Issue'
							,contents: {
								Country: {
									type: 'field'
									,dataType: 'listValue'
									,isRequired: function(){return false}
									,description: 'Country of Issue'	
									,listName: 'country'				
								}
								,ProvState: {
									type: 'field'
									,dataType: 'listValue'
									,isRequired: function(){return false}
									,description: 'Prov of Issue'
									,listName: 'provState'					
								}
							}					
						}
						,OtherDscrp: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Other desc.'										
						}						
					}
				}
			}
		}											
		,jobClass: {
		 	type: 'field'
		 	,dataType: 'listValue'
			,isRequired: function(){return false}
			,description: 'Job class'
			,listName: 'profGrpCode'								
		 }
		 ,occupationName: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Occupation name'								
		 }
		 ,birthPlace: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Birth place'								
		 }
		 ,nationality: {
		 	type: 'field'
		 	,dataType: 'listValue'
			,isRequired: function(){return false}
			,description: 'Nationality'
			,listName: 'country'								
		 }
		 ,countryOfBirth: {
		 	type: 'field'
		 	,dataType: 'listValue'
			,isRequired: function(){return false}
			,description: 'Country of birth'
			,listName: 'country'								
		 }
		 ,riskLevel: {
		 	type: 'field'
		 	,dataType: 'listValue'
			,isRequired: function(){return false}
			,description: 'Risk Level'
			,listName: 'RiskLevel'								
		 }
		 ,lang: {
		 	type: 'field'
		 	,dataType: 'listValue'
			,isRequired: function(){return true}
			,description: 'Language'
			,listName: 'lang'								
		 }
		 ,hPhone: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Home phone number'								
		 }
		 ,oPhone: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Business phone number'								
		 }											 
		 ,oExt: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Business extension'								
		 }
		  ,secPhone: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Secondary phone number'								
		 }											 
		 ,secExt: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Secondary extension'								
		 }
		 ,fax: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Fax number'								
		 }
		 ,email: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Email address'								
		 }
		 ,secEmail: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Second email address'								
		 }
		 ,EUSDJuris: {
		 	type: 'field'
			,dataType: 'listValue'
			,isRequired: function(){return false}
			,listName: 'country'
			,description: 'EUSD jurisdiction'
		 }
		 ,EUSDDeff: {
		 	type: 'field'
			,dataType: 'date'
			,isRequired: function(){return false}
			,description: 'EUSD effective date'
		 }
		 ,EUSDOption: {
		 	type: 'field'
			,dataType: 'listValue'
			,isRequired: function(){return false}
			,description: 'EUSD option'
			,listName: 'EUSDOption'
		 }
	}
};




var _gnAcctSetup_address = {
	type: 'node'
	,isRequired: function(node){return node.parentNode.id == 'Owner'}
	,contents: {
		addressLn1: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return true}
			,description: 'Address line 1'					
		}
		,addressLn2: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Address line 2'								
		}
		,addressLn3: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return false}
			,description: 'Address line 3'								
		}
		,city: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(){return true}
			,description: 'City'								
		}
		,provState: {
		 	type: 'field'
		 	,dataType: 'listValue'
			,isRequired: function(node){return false}
			,description: 'Province/State'
			,listName: 'provState'								
		}
		,country: {
		 	type: 'field'
		 	,dataType: 'listValue'
			,isRequired: function(){return true}
			,description: 'Country'
			,listName: 'country'								
		}
		,postalZip: {
		 	type: 'field'
		 	,dataType: 'string'
			,isRequired: function(node){return node.parentNode.getNodeValue('country') == 'CAN'}
			,description: 'Postal Code/Zip'
			,note: 'Required if coutry is Canada or USA'								
		}
	}
};


API.gnAcctSetupRequest = {			
	type: 'node'
	,isRequired: function(){return true}	
	,description: 'Account Setup'		
	,contents: {
		AcctSetup: {
			type: 'node'
			,isRequired: function(){return true}									
			,contents: {					
				actionCode: {						
					type: 'field'
					,dataType: 'string'					
					,description: 'Action Code'
					,isRequired: function(){return true}					
				}
				,deff: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return true}		
					,description: 'Acct Eff. Date'
					,defaultValue: DesktopWeb.Util.getDateString(new Date(), 'Ymd')				
				}
				,Dlr: {
					type: 'node'
					,isRequired: function(){return true}
					,description: 'Dealer Info.'
					,contents: {														
						dlrCode: {
							type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'Broker'
						 }
						 ,branchCode: {
						 	type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Branch'
						 }
						 ,repCode: {
						 	type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Sales Rep'								
						 }
						 ,dlrAcctID: {
						 	type: 'field'
						 	,dataType: 'string'							
							,description: 'Dealer account number'
							,isRequired: function(){return SmartFormsApp.DataStore.getNodeValue('gnAcctSetupRequest.AcctSetup.AcctInfo.acctDesig') == '2'}							
						 }																					
					}												 		
				}
				,AcctInfo: {
					type: 'node'
					,isRequired: function(){return true}
					,description: 'Account Info.'
					,contents: {
						acctDesig: {
						 	type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'Account designation'
							,listName: 'acctDesig'								
						 }	
						 ,acctType: {
						 	type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'Account type'
							,listName: 'acctType'								
						 }	
						 ,recipCode: {
						 	type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'Recipient code'
							,listName: 'recipCode'										
						 }	
						 ,taxCode: {
						 	type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'Tax jurisdiction'
							,listName: 'country'								
						 }
						 ,spousalFlg: {
						 	type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Spousal Flag'								
						 }
						 ,lckdInCode: {
						 	type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Locked in flag'								
						 }
						 ,shGroup: {
						 	type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return false}							
							,description: 'Shareholder group'
							,listName: 'shGroup'								
						 }									 		
					}
				}
				,Owner: {
					type: 'node'
					,isRequired: function(){return true}
					,description: "Owner Info."
					,contents: {
						ClientInfo: _gnAcctSetup_clientInfo
						,Address: _gnAcctSetup_address
					}
				}
				,Int: {
					type: 'node'
					,isRequired: function(){return false}
					,description: 'Intermediary Account Info.'
					,contents: {
						intCode: {
						 	type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Intermediary code'							
						 }	
						 ,intAcctID: {
						 	type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Intermediary account number'								
						 }	
					}
				}				
				,DthBenDtl: {
					type: 'node'
					,isRequired: function(node){return node.hasData()}					
					,contents: {
						DthBen: {
							type: 'node'
							,isRequired: function(node){return node.hasData() }
							,description: 'Beneficiary Details'
							,repeatCount: 5
							,contents: {
								benType: {
									type: 'field'
									,dataType: 'listValue'
									,isRequired: function(){return true}
									,description: 'Type of beneficiary'
									,listName: 'benType'									
								}
								,benRel: {
									type: 'field'
									,dataType: 'listValue'
									,isRequired: function(){return true}
									,description: 'Relationship to owner'
									,listName: 'benRel'
								}
								,benSplit: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: '% of benefit'
								}
								,ClientInfo: _gnAcctSetup_clientInfo
								,Address: _gnAcctSetup_address		
							}
						}						
					}
				}				
				,Jnt: {
					type: 'node'					
					,isRequired: function(node){return node.hasData()}
					,description: 'Joint Info.'
					,contents: {
						jntSurType: {
						 	type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'Type of joint account'
							,listName: 'jntSurType'																
						}
						,jntSigType: {
						 	type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'Joint disposition'
							,listName: 'jntSigType'																
						}
						,jntOwner: {
							type: 'node'
							,isRequired: function(){return true}
							,contents: {
								ClientInfo: _gnAcctSetup_clientInfo							
								,Address: _gnAcctSetup_address								
							}
						}
					}
				}
				,Spousal: {
					type: 'node'
					,isRequired: function(){return SmartFormsApp.DataStore.getNodeValue('gnAcctSetupRequest.AcctSetup.AcctInfo.spousalFlg') == 'y'}
					,description: "Spousal Info."
					,contents: {
						ClientInfo: _gnAcctSetup_clientInfo								
						,Address: _gnAcctSetup_address		
					}
				}
				,TFSASucsr: {
					type: 'node'
					,isRequired: function(node){return node.hasData()}
					,description: "TFSA Successor Info."
					,contents: {
						ClientInfo: _gnAcctSetup_clientInfo								
						,Address: _gnAcctSetup_address		
					}
				}						
				,StopFlags: {
					type: 'node'
					,isRequired: function(){return false}
					,description: 'Stop Flags'
					,contents: {
						purStop: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Stop Purchase'
						}	
						,redStop: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Stop Redeem'
						}	
						,xferInStop: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Stop Transer In'
						}	
						,xferOutStop: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Stop Transer Out'
						}	
					}
				}
				,ITF: {
					type: 'node'
					,isRequired: function(node){return node.hasData()}					
					,contents: {
						ITFBen: {
							type: 'node'
							,isRequired: function(node){return node.hasData()}
							,description: "ITF Info."
							,repeatCount: 4
							,contents: {
								ClientInfo: _gnAcctSetup_clientInfo	
							}
						}
					}
				}
				,SegInfo: {
					type: 'node'
					,isRequired: function(node){return node.hasData()}					
					,contents: {
						copyOwner: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Copy Owner Info.'
						}
						,Annuitant: {
							type: 'node'
							,isRequired: function(node){return node.parentNode.getNodeValue('copyOwner') == ""}
							,description: "Annuitant Info."
							,contents: {
								ClientInfo: _gnAcctSetup_clientInfo
								,Address: _gnAcctSetup_address
							}
						}
						,SucsrAnnuitant: {
							type: 'node'
							,isRequired: function(node){return node.hasData()}
							,description: "Successor Annuitant"
							,contents: {									
								ClientInfo: _gnAcctSetup_clientInfo
								,Address: _gnAcctSetup_address
							}
						}
						,SucsrOwner: {
							type: 'node'
							,isRequired: function(node){return node.hasData()}
							,description: "Successor Owner"
							,contents: {									
								ClientInfo: _gnAcctSetup_clientInfo
								,Address: _gnAcctSetup_address
							}
						}
						,CntgtDthBenDtl: {
							type: 'node'
							,isRequired: function(node){return node.hasData()}
							,contents: {
								DthBen: {
									type: 'node'
									,isRequired: function(){return true}
									,contents: {
										benType: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return true}
											,description: 'Type of beneficiary'
										}
										,benRel: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return true}
											,description: 'Relationship to owner'
										}
										,benSplit: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return false}
											,description: 'Percent of benefit'
										}
										,ClientInfo: _gnAcctSetup_clientInfo
										,Address: _gnAcctSetup_address
									}
								}
							}
						}
					}
				}									
				,LIPInfo: {
					type: 'node'
					,isRequired: function(){return false}
					,description: "LIP Info."
					,contents: {
						minWithAge: {
					 		type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Minimum withdrawal age'								
						}
						,uniSexPer: {
					 		type: 'field'
						 	,dataType: 'number'
							,isRequired: function(){return false}
							,description: 'Unisex (percentage) amount'								
						}
						,sexDistinctPer: {
					 		type: 'field'
						 	,dataType: 'number'
							,isRequired: function(){return false}
							,description: 'Sex distinct (percentage)'								
						}
						,penSource: {
					 		type: 'field'
						 	,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Pension source'								
						}
						,penJuris: {
					 		type: 'field'
						 	,dataType: 'listValue'
							,isRequired: function(){return true}
							,description: 'Pension jurisdiction'
							,listName: 'PenJuris'								
						}
					}
				}
			}				
		}
		,TEMP: {
			type: 'node'
			,isRequired: function(){return false}
			,contents: {
				newSalesRepCode: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'New Rep Code'
				}
				,acctType: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Account Type'			
				}				
			}
		}			
	}				
};