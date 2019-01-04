#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_grand_father_dated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_grand_father_dated() { }
		~CIFast_IFast_ifastcbo_err_ams_grand_father_dated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_GRAND_FATHER_DATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The AMS code has already stamped grand father date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The AMS code has already stamped grand father date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The AMS code has already stamped grand father date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille comporte déjà une date bénéficiant d'une clause de droits acquis marquée.")); }

        // Actions
	};
}



