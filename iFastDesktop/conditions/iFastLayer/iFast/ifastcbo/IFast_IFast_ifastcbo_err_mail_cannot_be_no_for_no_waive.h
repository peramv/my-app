#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mail_cannot_be_no_for_no_waive : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mail_cannot_be_no_for_no_waive() { }
		~CIFast_IFast_ifastcbo_err_mail_cannot_be_no_for_no_waive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mail can not be set to NO before consent is set to YES for %DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mail darf nicht auf NEIN gestellt werden, bevor die Einwilligung auf JA für %DOCTYPE% gestellt wurde.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No puede configurarse Correo en NO antes de configurar el consentimiento en SÍ para %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Courrier ne peut être réglé à Non avant que le champ Consentement ne soit réglé à Oui pour %DOCTYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Post kan niet zijn ingesteld op NEE voordat toestemming is ingesteld op JA voor documenttype %DOCTYPE%")); }

        // Actions
	};
}



