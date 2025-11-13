pipeline {
  agent {
    docker {
      image 'ubuntu:22.04'   // Run each build in a clean Ubuntu container
      args '-u root -v /var/run/docker.sock:/var/run/docker.sock' // Run as root and mount Docker socket
    }
  }

  environment {
    IMAGE = "cpp-crow-dashboard:latest"
  }

  stages {

    stage('Checkout') {
      steps {
        echo "📦 Cloning source code..."
        git url: 'https://github.com/kunjbhuva7/cpp-crow-dashboard.git', branch: 'main'
      }
    }

    stage('Install Dependencies') {
      steps {
        echo "⚙️ Installing dependencies (cmake, g++, git)..."
        sh '''
          apt-get update -y
          apt-get install -y cmake g++ git docker.io curl
        '''
      }
    }

    stage('Build with CMake') {
      steps {
        echo "🏗️ Building C++ project with CMake..."
        sh '''
          rm -rf build
          cmake -S . -B build
          cmake --build build -j$(nproc)
        '''
      }
    }

    stage('Build Docker Image') {
      steps {
        echo "🐳 Building Docker image..."
        sh 'docker build -t ${IMAGE} .'
      }
    }

    stage('Run Locally') {
      steps {
        echo "🚀 Running container locally on port 9999..."
        sh '''
          docker stop crow_dashboard || true
          docker rm crow_dashboard || true
          docker run -d --name crow_dashboard -p 9999:9999 ${IMAGE}
          sleep 3
          echo "🌍 Health check:" 
          curl -I http://localhost:9999/health || true
        '''
      }
    }
  }

  post {
    success {
      echo "✅ Dashboard is up and running at: http://localhost:9999"
    }
    failure {
      echo "❌ Pipeline failed. Please check Jenkins logs."
    }
  }
}

