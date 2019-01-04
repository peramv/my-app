#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batchname_should_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batchname_should_blank() { }
		~CIFast_IFast_ifastdbrkr_err_batchname_should_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCHNAME_SHOULD_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch Name should be blank for search by user.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batch Name should be blank for search by user.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch-Name sollte für eine Suche nach Benutzer leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El nombre de lote debe estar en blanco para la búsqueda por usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Nom du lot devrait être vide pour une recherche par utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batchnaam moet leeg zijn voor zoeken op gebruiker")); }

        // Actions
	};
}



