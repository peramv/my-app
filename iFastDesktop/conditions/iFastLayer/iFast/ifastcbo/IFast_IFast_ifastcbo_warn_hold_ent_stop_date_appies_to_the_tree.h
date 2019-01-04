#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_hold_ent_stop_date_appies_to_the_tree : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_hold_ent_stop_date_appies_to_the_tree() { }
		~CIFast_IFast_ifastcbo_warn_hold_ent_stop_date_appies_to_the_tree() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_HOLD_ENT_STOP_DATE_APPIES_TO_THE_TREE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Holding Entity Stop Date change will be applied to the whole tree and it's irreversible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La modification de la date de fin de l’entité de portefeuille sera appliquée à l’ensemble de l’arbre et sera irréversible.")); }

        // Actions
	};
}



