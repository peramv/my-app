#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_i18n_mask_format_error : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_i18n_mask_format_error() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_i18n_mask_format_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_I18N_MASK_FORMAT_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error formatting value %VALUE%, with display mask %DISPMASK%, and host mask %HOSTMASK%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error formatting value %VALUE%, with display mask %DISPMASK%, and host mask %HOSTMASK%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler beim Formatieren des Wertes %VALUE%, mit der Anzeigemaske %DISPMASK% und der Hostmaske %HOSTMASK%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al formatear el valor %VALUE%, con máscara de visualización %DISPMASK%, y máscara de host %HOSTMASK%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors du formatage de la valeur %VALUE% avec le masque de l'affichage %DISPMASK% et le masque de l'hôte %HOSTMASK%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij formatteren waarde %VALUE%, met weergavemasker %DISPMASK% en hostmasker %HOSTMASK%")); }

        // Actions
	};
}



