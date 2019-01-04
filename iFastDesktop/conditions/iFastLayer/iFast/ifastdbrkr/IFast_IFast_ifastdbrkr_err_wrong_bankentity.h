#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_wrong_bankentity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_wrong_bankentity() { }
		~CIFast_IFast_ifastdbrkr_err_wrong_bankentity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_BANKENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Banking Entity must be either 10, 02, 03 or 04.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Banking-Objekt muss entweder 10, 02, 03 oder 0,4 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La entidad bancaria debe ser 10, 02, 03 ó 04")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité bancaire doit être 10, 02, 03 ou 04.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bankeenheid moet 10, 02, 03 of 04 zijn")); }

        // Actions
	};
}



