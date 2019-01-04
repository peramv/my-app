#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawdi_diawdi_logon_user_disabled : public CConditionObject
	{
	public:
		CIFast_IFast_diawdi_diawdi_logon_user_disabled() { }
		~CIFast_IFast_diawdi_diawdi_logon_user_disabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_USER_DISABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unrecognized email format. Email addresses should follow the format \"name@domainname.dnssearchorder\" ie: \"my.name@mydomain.com\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Format de courrier electronique non reconnu. Les adresses electroniques devraient être au format \"name@domainname-dnsearchorder\" c'est-a-dire \"my.name@mydomain.com\"")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("E-Mail-Format wurde nicht erkannt. E-Mail-Adressen sollten folgendes Format haben „name@domainname.dnssearchorder“, z.B.: \"my.name@mydomain.com\"")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Formato de e-mail no reconocido. Las direcciones de e-mail deben tener el formato \"nombre@nombrededominio.ordendebúsquedadns\", p. ej.: \"mi.nombre@midominio.com\"")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de courriel non reconnu. Les adresses courriel devraient être en format « nom@messagerie.domaine », c.-à-d. : « mon.nom@mamessagerie.com ».")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onbekende e-mailindeling. E-mailadressen moeten de indeling 'naam@domeinnaam.dnszoekvolgorde' volgen, zoals: ?mijn.naam@mijndomein.com?")); }

        // Actions
	};
}



