#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_waive_paper_cannot_be_yes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_waive_paper_cannot_be_yes() { }
		~CIFast_IFast_ifastcbo_err_waive_paper_cannot_be_yes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WAIVE_PAPER_CANNOT_BE_YES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Waive paper can not be set to yes when CD, FAX, EMAIL and EPOST are all set to no for document type:  %DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verzichten auf Papier kann nicht auf \"Ja\" gestellt werden, wenn CD, FAX und EMAIL für diese Dokumentart alle auf Nein gestellt sind:  %DOCTYPE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No puede configurarse Renuncia a documentos impresos en Sí cuando CD, FAX y EMAIL están configurados como No para tipo de documento:  %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le document de renonciation ne peut être réglé à Oui quand les champs CD, Télécopieur, Courriel et Postel sont tous réglés à Non pour le type de document : %DOCTYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Papier achterwege laten kan niet op ja worden ingesteld als CD, FAX en E-MAIL allemaal zijn ingesteld op nee voor dit documenttype:  %DOCTYPE%")); }

        // Actions
	};
}



