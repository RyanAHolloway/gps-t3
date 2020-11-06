pipeline {
     agent any

      options {
           buildDiscarder(logRotator(numToKeepStr: '10'))
      }

      parameters {
           booleanParam name: 'RUN_TESTS', defaultValue: true, description: 'Run Tests?'
           booleanParam name: 'RUN_ANALYSIS', defaultValue: true, description: 'Run Static Code Analysis?'
           booleanParam name: 'DEPLOY', defaultValue: true, description: 'Deploy Artifacts?'
      }

      stages {
           stage('Build') {
                steps {
                     sh 'make -f Makefile2 all'
                }
           } 
     }
}
