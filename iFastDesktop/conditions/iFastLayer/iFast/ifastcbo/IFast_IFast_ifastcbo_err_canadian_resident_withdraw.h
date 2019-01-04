#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_canadian_resident_withdraw : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_canadian_resident_withdraw() { }
		~CIFast_IFast_ifastcbo_err_canadian_resident_withdraw() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANADIAN_RESIDENT_WITHDRAW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Withdrawal can only be made by Canadian Resident.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Abhebung kann nur von einem Einwohner Kanadas vorgenommen werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El retiro sólo puede ser realizado por un residente canadiense")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le retrait ne peut être fait que par un résident canadien.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opname kan alleen worden gedaan door Canadees staatsburger")); }

        // Actions
	};
}



