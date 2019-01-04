#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record() { }
		~CIFast_IFast_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COULD_NOT_CREATE_THE_SHAREHOLDER_REMARKS_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not create the shareholder remarks record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de creer l'enregistrement des remarques relatives a l'actionnaire")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Eintrag mit den Kommentaren des Aktionärs konnte nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se pudo crear el registro de comentarios del accionista")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de créer l'enregistrement des remarques de l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het opmerkingenrecord voor de aandeelhouder kon niet worden gemaakt")); }

        // Actions
	};
}



