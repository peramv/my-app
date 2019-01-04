#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdata_cnd_invalidmaskexception : public CConditionObject
	{
	public:
		CBase_Ifds_bfdata_cnd_invalidmaskexception() { }
		~CBase_Ifds_bfdata_cnd_invalidmaskexception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CND_InvalidMaskException")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdata")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There was an internal problem.  The field's mask is not formatted correctly.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Stückzinsen-Informationen verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There was an internal problem.  The field's mask is not formatted correctly.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a eu un problème interne. Le masque du champ n'est pas mis en forme correctement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("There was an internal problem.  The field's mask is not formatted correctly.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact a support representative and report this message.")); }
	};
}



