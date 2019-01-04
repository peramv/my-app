#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_alloc_systematic_on_clan_plan : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_alloc_systematic_on_clan_plan() { }
		~CIFast_IFast_ifastcbo_err_no_alloc_systematic_on_clan_plan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ALLOC_SYSTEMATIC_ON_CLAN_PLAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocated systematics are not permitted on Clan Plan accounts.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocated systematics are not permitted on Clan Plan accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugeteilte Systematische Pläne sind für Clanplan-Konten nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten planes sistemáticos asignados en las cuentas Clan Plan.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les systématiques réparties ne sont pas autorisées pour les comptes de régime de clan.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gealloceerde systeemplannen zijn niet toegestaan voor Clan Plan accounts")); }

        // Actions
	};
}



