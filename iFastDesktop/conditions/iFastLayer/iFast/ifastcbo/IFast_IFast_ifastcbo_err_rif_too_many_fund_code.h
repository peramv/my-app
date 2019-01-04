#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_too_many_fund_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_too_many_fund_code() { }
		~CIFast_IFast_ifastcbo_err_rif_too_many_fund_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_TOO_MANY_FUND_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Number of allocated funds must be less then %FUND_ALLOC_LIMIT%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le nombre de fonds attribues doit être inferieur a %FUND_ALLOC_LIMIT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anzahl der zugewiesenen Fonds muss kleiner als %FUND_ALLOC_LIMIT% sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de fondos asignados debe ser inferior a %FUND_ALLOC_LIMIT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nombre de fonds répartis doit être inférieur à %FUND_ALLOC_LIMIT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aantal gealloceerde fondsen moet kleiner zijn dan %FUND_ALLOC_LIMIT%")); }

        // Actions
	};
}



