#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amscode_target_asset_mix : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amscode_target_asset_mix() { }
		~CIFast_IFast_ifastcbo_err_invalid_amscode_target_asset_mix() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMSCODE_TARGET_ASSET_MIX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid AMS Code for Target Asset Mix.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid AMS Code for Target Asset Mix.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid AMS Code for Target Asset Mix.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille est invalide pour la composition d'actif cible.")); }

        // Actions
	};
}



