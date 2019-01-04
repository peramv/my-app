/*********************************************************************************************
 * @file	RDSPTransactionsInterface.Resources.js
 * @author	Danil Gorelic
 * @desc	Resources JS file for RDSPTransactionsInterface.
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var currRecord = 0;
	var pageSize = 100;
	// content dimensions
	var _layoutHeight = 885;
	var _layoutWidth = 750;
	
	function getDescription(recordType, transType) {
		for(var index = 0; index < _translationMap['TransactionDescriptions'].length; ++index) {
			var description = _translationMap['TransactionDescriptions'][index];
			if (description.key.recordType === recordType && description.key.transType === transType) {
				return description.text;
			}
		}
		
		return "";
	}
	
	var checkColumn = new Ext.grid.CheckColumn({
 		width: 16,
		dataIndex: 'checked'
	});
	// **** buttons ****
	var _buttons = {
	okScreenButton :new DesktopWeb.Controls.ScreenButton({
			itemId : 'okBtnScreen',
			text: _translationMap['OK']
			,handler: _controller.updateStatus
			,disabled : true
		}
	)
	,cancelScreenButton : new DesktopWeb.Controls.ScreenButton(
	{
		text: _translationMap['Cancel']
		,handler: function(){
			if (_controller.updatesFlag){
				DesktopWeb.Util.displayDiscardPrompt(function(ok) {
					if(ok) DesktopWeb.Util.cancelScreen();
				});
			}else{
				DesktopWeb.Util.cancelScreen();
			}
		}
	}),
	refreshBtn: new DesktopWeb.Controls.ActionButton({
        text: _translationMap["Refresh"],
        style: 'margin-left: 115px;margin-bottom: 4px;',
        listeners: {
            click: function () {
            	currRecord = 0;
            	_controller.refresh(0, pageSize);
            }
        }
    }),
    moreBtn: new DesktopWeb.Controls.ActionButton({
		itemId: 'moreBtn'
		,text: _translationMap['More']
		,handler: function(){
			currRecord += _grids['rdspTransGrid'].getStore().getCount();
			_controller.refresh(currRecord, pageSize);
		}
	})
	}

	// **** fields ****
	var _fields = {
		RecordDetails : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['RecordDetails']
		}),
		FileTypeLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['FileType']
		}),
		FileType: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'FileType'
			,fieldLabel: _translationMap["FileType"]
			,width: 110,
	        valueField: 'value',
	        listeners : {
	        	select: function (combo, record, index) {
	        		_fields.Status.setValue("All");
	        		_fields.Status.setDisabled(record.data.code === '02');
	        		_fields.NewStatus.setDisabled(record.data.code === '02');
                }
	        }
		}),
		RecordTypeLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['RecordType'],
			width : 50
		}),
		RecordType: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'recordType'
			,fieldLabel: _translationMap["RecordType"]
			,width: 110
			,valueField: 'value'
		}),	
		SpecifiedRunNoCurrLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['SpecifiedRunNoCurr'],
			width : 50
		}),
		Status: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'status'
			,fieldLabel: _translationMap["Status"]
			,width: 110
			,valueField: 'value'
		}),
		NewStatus: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'newStatus',
			fieldLabel: _translationMap["NewStatus"],
	        width: 120,
	        valueField: 'value',
	        listeners : {
	        	select: function (combo, record, index) {
	        		if (_controller.updatesFlag = _grids['rdspTransGrid'].dirty) {
	        			_buttons['okScreenButton'].enable();
	        		}
                }
	        }
	    })
	,
	AccountNo : new DesktopWeb.Controls.TextField({
		fieldLabel : _translationMap['AccountNo'],
		style : 'padding-left:5px;',
		allowBlank : true,
		width : 110,
		emptyText: 'All',
	    minLength: 4,
	    maxLength: 15,
	    maskRe:/[0-9]/i
	})
    ,holderSinOrBnLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['HolderSinOrBn']
	   }),
	   primaryCaregiverSinOrAgencyBnLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['PrimaryCaregiverSinOrAgencyBn']
	   }),
	   cityLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['City']
	   }),
	   issuerBnLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['IssuerBn']
	   }),
	   contractCreationOrUpdateDateLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['ContractCreationOrUpdateDate']
	   }),
	   primaryCaregiverSurnameOrAgencyNameLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['PrimaryCaregiverSurnameOrAgencyName']
	   }),
	   updateDateLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['UpdateDate']
	   }),
	   holderSurnameOrHolderAgencyNameLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['HolderSurnameOrHolderAgencyName']
	   }),
	   languageLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['Language']
	   }),
	   closureReasonDateLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['ClosureReasonDate']
	   }),
	   closureDateLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['ClosureDate']
	   }),
	   addressLine1Label : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['AddressLine1']
	   }),
	   closureReasonLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['ClosureReason']
	   }),
	   holderRelationshipLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['HolderRelationship']
	   }),
	   issuerTransactionNumberLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['IssuerTransactionNumber']
	   }),
	   beneficiarySexLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['BeneficiarySex']
	   }),
	   primaryCaregiverNameLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['PrimaryCaregiverName']
	   }),
	   addressLine3Label : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['AddressLine3']
	   }),
	   addDateLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['AddDate']
	   }),
	   postalCodeLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['PostalCode']
	   }),
	   specimenPlanLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['SpecimenPlan']
	   }),
	   holderDateOfBirthLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['HolderDateOfBirth']
	   }),
	   otherSpecimenPlanLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['OtherSpecimenPlan']
	   }),
	   holderGivenNameLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['HolderGivenName']
	   }),
	   primaryCaregiverTypeLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['PrimaryCaregiverType']
	   }),
	   transferIndicatorLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['TransferIndicator']
	   }),
	   transactionTypeLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['TransactionType']
	   }),
	   addressLine2Label : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['AddressLine2']
	   }),
	   recordTypeLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['RecordType']
	   }),
	   beneficiarySurnameLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['BeneficiarySurname']
	   }),
	   beneficiaryGivenNameLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['BeneficiaryGivenName']
	   }),
	   beneficiarySinLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['BeneficiarySin']
	   }),
	   holderSexLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['HolderSex']
	   }),
	   contractLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['Contract']
	   }),
	   holderTypeLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['HolderType']
	   }),
	   provinceLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['Province']
	   }),
	   countryLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['Country']
	   }),
	   beneficiaryDateOfBirthLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['BeneficiaryDateOfBirth']
	   }),
	   otherContractLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['OtherContract']
	   }),
	   contractSignatureDateLabel : new DesktopWeb.Controls.Label({
	   	 fieldLabel : _translationMap['ContractSignatureDate']
	   }),
	   removalDateLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['RemovalDate']
		   }),
	   contributionDateLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ContributionDate']
		   }),
	   primaryCaregiverSin1OrAgencyBnLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverSin1OrAgencyBn']
		   }),
	   bondRequestDateLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['BondRequestDate']
		   }),
		grantRequestedLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['GrantRequested']
		   }),
		   primaryCaregiverSurname1OrAgencyNameLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverSurname1OrAgencyName']
		   }),
		   primaryCaregiverType1Label : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverType1']
		   }),
		   primaryCaregiverType2Label : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverType2']
		   }),	   
		   primaryCaregiverGivenName2Label : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverGivenName2']
		   }),
		   primaryCaregiverSin2OrAgencyBnLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverSin2OrAgencyBn']
		   }),
		   certificationDateLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['CertificationDate']
		   }),
		   transactionDateLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['TransactionDate']
		   }),
		   primaryCaregiverSurname2OrAgencyNameLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverSurname2OrAgencyName']
		   }),
		   primaryCaregiverGivenName1Label : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PrimaryCaregiverGivenName1']
		   }),
		   contributionAmountLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ContributionAmount']
		   }),	 
		   primaryCaregiverGivenNameLabel : new DesktopWeb.Controls.Label({
			 fieldLabel : _translationMap['PrimaryCaregiverGivenName']
		   }),
		   retirementSavingRolloverAmountLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['RetirementSavingRolloverAmount']
		   }),
		   retirementSavingRolloverDateLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['RetirementSavingRolloverDate']
		   }),	
		   transactionOriginLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['TransactionOrigin']
		   }),
		   originalIssuerBNLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['OriginalIssuerBN']
		   }),
		   OriginalTransactionNumberLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['OriginalTransactionNumber']
		   }),
		   contractNumberLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ContractNumber']
		   }),	 
		   electionPeriodStartDateLabel : new DesktopWeb.Controls.Label({
			 fieldLabel : _translationMap['ElectionPeriodStartDate']
		   }),
		   electionPeriodEndDateLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ElectionPeriodEndDate']
		   }),
		   educationSavingRolloverAmountLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['EducationSavingRolloverAmount']
		   }),
	       educationSavingRolloverDateLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['EducationSavingRolloverDate']
		   }),
		   reportingDateLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ReportingDate']
		   }),
		   fmvAmountLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['FmvAmount']
		   }),
		   transactionNumberLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['TransactionNumber']
		   }),
		   grantAmountLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['GrantAmount']
		   }),
		   bondAmountLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['BondAmount']
		   }),
		   dateOfPaymentLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['DateOfPayment']
		   }),
		   refusalReasonLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['RefusalReason']
		   }),
		   originalIssuerBnLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['OriginalIssuerBn']
		   }),
		   OriginalTransactionNumberLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['OriginalTransactionNumber']
		   }),
		   paymentRequisitionedLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['PaymentRequisitioned']
		   }),
		   cdspSystemDateLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['CdspSystemDate']
		   }),
		   cdspSystemSinLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['CdspSystemSin']
		   }),
		   addConsentDateLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['AddConsentDate']
		   }),
		   consentSinOrBnLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ConsentSinOrBn']
		   }),
		   consentGivenNameLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ConsentGivenName']
		   }),
		   consentSurnameOrAgencyNameLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ConsentSurnameOrAgencyName']
		   }),
		   consentTypeLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ConsentType']
		   }),
		   revokeConsentDateLabel	:new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['RevokeConsentDate']
		   }),
		   beneficiaryDtcEligibilityYearLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BeneficiaryDtcEligibilityYear']
		   }),
		   beneficiaryDtcEligibiltyStatusLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BeneficiaryDtcEligibiltyStatus']
		   }),
		   beneficiaryDtcUndeterminedReasonLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BeneficiaryDtcUndeterminedReason']
		   }),
		   
		   
		   
		   dapDateLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['DapDate']
		   }),
		   contributionPortionOfTheNonTaxableFormulaLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['ContributionPortionOfTheNonTaxableFormula']
		   }),
		   grantPortionOfTheDapLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['GrantPortionOfTheDap']
		   }),
		   bondPortionOfTheDapLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BondPortionOfTheDap']
		   }),
		   nonTaxablePortionOfTheDapLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['NonTaxablePortionOfTheDap']
		   }),
		   totalDapAmountLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['TotalDapAmount']
		   }),
		   dapRetirementSavingsRolloverAmountLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['DapRetirementSavingsRolloverAmount']
		   }),
		   ldapDateLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['LdapDate']
		   }),
		   grantPortionOfTheLdapLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['GrantPortionOfTheLdap']
		   }),
		   bondPortionOfTheLdapLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BondPortionOfTheLdap']
		   }),
		   nonTaxablePortionOfTheLdapLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['NonTaxablePortionOfTheLdap']
		   }),
		   totalLdapAmountLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['TotalLdapAmount']
		   }),
		   ldapRetirementSavingsRolloverAmountLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['LdapRetirementSavingsRolloverAmount']
		   }),
		   repaymentDateLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['RepaymentDate']
		   }),
		   grantRepaymentAmountLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['GrantRepaymentAmount']
		   }),
		   bondRepaymentAmountLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BondRepaymentAmount']
		   }),
		   grantTerminationAdjustmentAmountLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['GrantTerminationAdjustmentAmount']
		   }),
		   bondterminationAdjustmentAmountLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BondterminationAdjustmentAmount']
		   }),
		   repaymentReasonLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['RepaymentReason']
		   }),
		   fieldNameLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['FieldName']
		   }),
		   errorCodeLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['ErrorCode']
		   }),
		   sinIssueLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['SinIssue']
		   }),
		   givenNameIssueLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['GivenNameIssue']
		   }),
		   surnameIssueLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['SurnameIssue']
		   }),
		   birthDateIssueLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['BirthDateIssue']
		   }),
		   sexIssueLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['SexIssue']
		   }),
		   sinLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['Sin']
		   }),
		   originalIssuerTransactionNumberLabel:new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['OriginalIssuerTransactionNumber']
		   }),
		   stopRequestDateLabel :new DesktopWeb.Controls.Label({
			   	 fieldLabel : _translationMap['StopRequestDate']
		   }),
		   currentContractStatusLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentContractStatus']
		     }),
		   contractInformationPassesTransactionValidationLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['ContractInformationPassesTransactionValidation']
		     }),
		   contractInformationPasses60DayRuleLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['ContractInformationPasses60DayRule']
		     }),
		   contractInformationContainsMinimumInformationRequirementsLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['ContractInformationContainsMinimumInformationRequirements']
		     }),
		   beneficiarySinPassesIdentityValidationAtSirLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['BeneficiarySinPassesIdentityValidationAtSir']
		     }),
		   holdersSinPassesIdentityValidationAtSirLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['HoldersSinPassesIdentityValidationAtSir']
		     }),
		   currentContractIsWaitingForATransferToOccurLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentContractIsWaitingForATransferToOccur']
		     }),
		   beneficiaryPassesResidencyValidationAtContractSignatureDateLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['BeneficiaryPassesResidencyValidationAtContractSignatureDate']
		     }),
		   beneficiaryPassesDtcEligibilityValidationAtContractSignatureDateLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['BeneficiaryPassesDtcEligibilityValidationAtContractSignatureDate']
		     }),
		   beneficiarySinIsUsableAtContractSignatureDateLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['BeneficiarySinIsUsableAtContractSignatureDate']
		     }),
		   holdersSinIsUsableAtContractSignatureDateLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['HoldersSinIsUsableAtContractSignatureDate']
		     }),
		   remainingBalanceOnContractLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['RemainingBalanceOnContract']
		     }),
		   currentReasonForChangeOfContractStatusLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentReasonForChangeOfContractStatus']
		     }),
		   currentTransferStatusLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentTransferStatus']
		     }),
		   currentResidencyEligibilityOfBeneficiaryLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentResidencyEligibilityOfBeneficiary']
		     }),
		   currentDtcEligibilityOfBeneficiaryLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentDtcEligibilityOfBeneficiary']
		     }),
		   currentBeneficiarySinUsabilityLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentBeneficiarySinUsability']
		     }),
		   currentHoldersSinUsabilityLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['CurrentHoldersSinUsability']
		     }),
		   contractRegistrationRetirementSavingsRolloverCompliantLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['ContractRegistrationRetirementSavingsRolloverCompliant']
		     }),
		   contractRegistrationEducationSavingsRolloverCompliantLabel:new DesktopWeb.Controls.Label({
		        fieldLabel : _translationMap['ContractRegistrationEducationSavingsRolloverCompliant']
		     }),

		   errorMessagesLabel : new DesktopWeb.Controls.Label({
		   	 fieldLabel : _translationMap['ErrorMessages']
		   })
	   ,placeHolder : new DesktopWeb.Controls.ColumnPlaceHolder({
	   })
	
	};

	
	// **** grids ****
	var _grids = {
	rdspAccountInfoGrid : new DesktopWeb.AdvancedControls.GridPanel({}),
	rdspTransGrid : new DesktopWeb.AdvancedControls.GridPanel({
		width: _layoutWidth-15
		,autoScroll: true
		,height: 330
		,sortable: true
		,dirty: false
		,plugins: checkColumn
		,store: new Ext.data.XmlStore(
		{
			record: 'records'
			,fields: [{name: 'checked', type: 'boolean'}, 'id', 'row', {name:'account', type:'int'}, 'transDate', 'esdcTransNo', 'recordType', 'transType', 'description', 'status']
			,listeners : {
		        update : function(records) {
		        	var grid = _grids['rdspTransGrid'];
		        	grid.dirty = false;
		        	
		        	for(var i = 0; i < records.data.length; ++i) {
		        		grid.dirty |= records.data.items[i].data.checked;
		        	} 
		        	
		        	_controller.updatesFlag = _fields['NewStatus'].getValue().length && grid.dirty;
					
		        	if (_controller.updatesFlag) {
		        		_buttons['okScreenButton'].enable();
		        	}
		        	else {
		        		_buttons['okScreenButton'].disable();
		        	}
		        }
		    }
		})
		,selModel: new Ext.grid.RowSelectionModel(
			{
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						var eventId = record.get('id');
						var rowNum = record.get('row'); 
						_controller.getIndividualEventLogDetails(eventId, rowNum);
					}
				}
			}
		)
		,viewConfig: { autoFill: true }
		,colModel: new Ext.grid.ColumnModel({
			defaults: {
				menuDisabled: true, sortable:true, width: 40
			}
			,columns: [
				checkColumn
				,{header: _translationMap['Account'], dataIndex: 'account', xtype:'numbercolumn', format: '0', width: 30}
				,{header: _translationMap['TransDate'], dataIndex: 'transDate', xtype:'datecolumn', format: 'd/m/Y'}
				,{header: _translationMap['ESDCTransNo'], dataIndex: 'esdcTransNo', xtype:'numbercolumn', format: '0', width: 50}
				,{header: _translationMap['RecordType'], dataIndex: 'recordType'}
				,{header: _translationMap['TransType'], dataIndex: 'transType'}
				,{header: _translationMap['TransDescr'], dataIndex: 'description', width: 70,
					renderer: function(value, meta, record){
						record.data.description = getDescription(record.data.recordType, record.data.transType)
	                    return record.data.description;
	                }
				}
				,{header: _translationMap['Status'], dataIndex: 'status', width: 50,
					renderer: function(value, meta, record) {
						meta.css = record.data.error ? 'err' : '';
					    return _translationMap.statusMap[value];
					}
				}	
			]
		})
	})
	}
	
	var detailsPanel = new Ext.Panel({
	    title: _translationMap["RecordDetails"],
	    width: _layoutWidth,
	    height: 200,
	    autoScroll:true,
	    cls:'panel'
	});
    
	// PUBLIC ITEMS
	return {
		panel : detailsPanel,
		layoutWidth: _layoutWidth
		,layoutHeight: _layoutHeight
		,fields: _fields
		,grids: _grids
		,buttons: _buttons
		,pageSize : pageSize
		,layout: new Ext.Container({
			height: _layoutHeight
			, width: _layoutWidth
                        , id: 'interfaceTransactions_id'
			, items: [{
				xtype: 'fieldset'
				,title: ''
				,items: [
					{
						layout: 'column'
						,items: [
							{
								columnWidth: 0.35
								,labelWidth: 100
								,layout: 'form'
								,items: [
									_fields['FileType']
									,_fields['RecordType']
								]
							}
							, {
								columnWidth: 0.35
								,labelWidth: 100
								,layout: 'form'
								,items: [
									_fields['Status']
									,_fields['AccountNo']
									
								]
							}
							, {
								columnWidth: 0.30
								,labelWidth: 100
								,layout: 'form'
								,items: [
									_fields['placeHolder'],
									[_buttons['refreshBtn']]
								]
							}
						]
					}	
				]}
				,new Ext.Container({
					items: [
						{
							xtype: 'fieldset'
							,title: _translationMap['RdspTransRecords']
							,items:[
								{
									layout: 'column'
									,items: [_grids['rdspTransGrid']]
								}
							]
						},
						{
							layout: 'column',
							items: [
								{
									columnWidth: 0.90
									,layout: 'form'
									,labelWidth: 200
									,items:[_fields['NewStatus']] 
								},
		                        {
									columnWidth: 0.10
									,layout: 'form'
		                        	,items: [
		                        		_buttons['moreBtn']
		                        	]
		                        }
							]
						}
					]
				})
				, {
                    xtype: 'fieldset',
                    title: _translationMap['RecordDetails'],
                    autoHeight:true,
                    items: [ {
						layout : 'column',											
						items : [									
								{
									layout : 'form',
									id: 'recordDetails-id1',
									autoHeight:true,
				                    columnWidth : 0.50,
				                    style : 'padding-left:18px;',
				                    labelWidth: 200
								},
								{
									layout : 'form',
									id: 'recordDetails-id2',
									autoHeight:true,
				                    columnWidth : 0.50,
				                    style : 'padding-left:18px;',
				                    labelWidth: 200
								}  
							]
						},
						{
							layout : 'column',											
							items : [	
									{
										layout : 'form',
										id: 'recordDetails-id3',
										autoHeight:true,
					                    style : 'padding-left:18px;',
					                    labelWidth: 100
									}  
								]
							}]
                }
					]}
		)
		,screenButtons: {
			items:[
				_buttons['okScreenButton'], _buttons['cancelScreenButton']
			]
		}
	}
}