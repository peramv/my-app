#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_mail_to_suppress : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_mail_to_suppress() { }
		~CIFast_IFast_ifastcbo_err_no_mail_to_suppress() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_MAIL_TO_SUPPRESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no Mail, Fax, CD, Email or Epost to suppress for document type:%DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für Dokument %DOCTYPE% kann keine Adresse, Fax, CD, Email unterdrückt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay Correo, Fax, CD, E-mail para suprimir para el tipo de documento:%DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucun Courrier, Télécopieur, CD, Courriel ou Postel à supprimer pour le type de document : %DOCTYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen post, fax, CD of e-mail om achterwege te laten voor dit documenttype:%DOCTYPE%")); }

        // Actions
	};
}



