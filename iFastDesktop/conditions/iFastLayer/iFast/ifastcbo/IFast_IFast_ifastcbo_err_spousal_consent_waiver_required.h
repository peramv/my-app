#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_spousal_consent_waiver_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_spousal_consent_waiver_required() { }
		~CIFast_IFast_ifastcbo_err_spousal_consent_waiver_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPOUSAL_CONSENT_WAIVER_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spousal consent/waiver required if annuity not in accordance with legislation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zustimmung/Verzichtserklärung des Ehepartners erforderlich, wenn Annuität nicht mit der Gesetzgebung übereinstimmt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere consentimiento/renuncia conyugal si la anualidad no se ajusta a la legislación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le consentement/la renonciation du conjoint est requis(e) si la rente n'est pas conforme à la législation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toestemming of verklaring van afstand van echtgenoot of echtgenote is vereist als de lijfrente niet volgens de wet is")); }

        // Actions
	};
}



