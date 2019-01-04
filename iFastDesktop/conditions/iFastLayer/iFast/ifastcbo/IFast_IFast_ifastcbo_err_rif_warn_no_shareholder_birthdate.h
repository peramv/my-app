#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_warn_no_shareholder_birthdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_warn_no_shareholder_birthdate() { }
		~CIFast_IFast_ifastcbo_err_rif_warn_no_shareholder_birthdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_WARN_NO_SHAREHOLDER_BIRTHDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spouse's birthday has not been entered and shareholder's birthday is unknown.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geburtsdatum des Ehepartners wurde nicht eingegeben und der Geburtstag des Aktionärs ist unbekannt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha introducido la fecha de nacimiento del cónyuge y no se conoce la del accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du conjoint n'a pas été saisie et celle du détenteur est inconnue.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum echtgenoot of echtgenote is niet ingevuld en de geboortedatum van de aandeelhouder is onbekend")); }

        // Actions
	};
}



