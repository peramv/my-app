#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_must_be_prior_to_last_processed_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_must_be_prior_to_last_processed_date() { }
		~CIFast_IFast_ifastcbo_err_start_date_must_be_prior_to_last_processed_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_MUST_BE_PRIOR_TO_LAST_PROCESSED_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Start date must be prior to last processed date %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Startdatum muss vor dem letzten verarbeiteten Datum %DATE% liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de inicio debe ser anterior a la última fecha procesada %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début doit être antérieure à la dernière date traitée %DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Begindatum moet eerder liggen dan laatste verwerkte datum %DATE%")); }

        // Actions
	};
}



