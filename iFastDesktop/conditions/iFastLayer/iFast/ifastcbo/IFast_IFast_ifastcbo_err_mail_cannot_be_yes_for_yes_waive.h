#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mail_cannot_be_yes_for_yes_waive : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mail_cannot_be_yes_for_yes_waive() { }
		~CIFast_IFast_ifastcbo_err_mail_cannot_be_yes_for_yes_waive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MAIL_CANNOT_BE_YES_FOR_YES_WAIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mail can not be set to YES, before consent is set to NO for %DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mail darf nicht auf JA gestellt werden, bevor die Einwilligung auf NEIN für %DOCTYPE% gestellt wurde.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No puede configurarse Correo en SÍ antes de configurar el consentimiento en NO para %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Courrier ne peut être réglé à Oui avant que le champ Consentement ne soit réglé à Non pour %DOCTYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Post kan niet zijn ingesteld op JA voordat toestemming is ingesteld op NEE voor documenttype %DOCTYPE%")); }

        // Actions
	};
}



