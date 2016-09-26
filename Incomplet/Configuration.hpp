/**
 * \file Configuration.hpp
 * \brief déclaration de la classe Configuration (incomplet)
 * \author S.B
 * \date 26/09/2016
 */

#ifndef CONFIGURATION_INCOMPLET_HPP
#define CONFIGURATION_INCOMPLET_HPP

#include <list>

namespace incomplet {

/**
 * \class Configuration
 * \brief représente une configuration des variables du problème
 */
class Configuration {

    public:

        /**
         * \brief constructeur
         */
        Configuration();

        /**
         * \brief génère le voisinage d'une configuration
         */
        void genererVoisinage(std::list<Configuration>& voisinage);

    private:

};

}

#endif // CONFIGURATION_INCOMPLET_HPP
