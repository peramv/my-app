#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_account_number_is_invalid : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_account_number_is_invalid() { }
		~CIFast_Infrastructure_ifastdbrkr_err_account_number_is_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUMBER_IS_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this batch number. Verify batch number and re-enter.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this batch number. Verify batch number and re-enter.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Batch-Nummer nicht. Bestätigen Sie die Batch-Nummer und geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de lote. Verifique el número de lote y vuelva a introducirlo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro de lot. Vérifiez le numéro de lot et réessayez.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit batchnummer niet. Controleer het batchnummer en voer het opnieuw in")); }

        // Actions
	};
}



