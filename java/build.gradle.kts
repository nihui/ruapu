plugins {
    id("java")
}

group = "ruapu"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.9.1"))
    testImplementation("org.junit.jupiter:junit-jupiter")
}

tasks.test {
    useJUnitPlatform()
}

val host: String = System.getProperty("os.name")!!

tasks.register("buildJNI") {
    doLast {
        val shell = when {
            host.startsWith("Windows") -> "powershell.exe"
            else -> "bash"
        }
        val script = when {
            host.startsWith("Windows") -> "build.ps1"
            else -> "build.sh"
        }
        exec {
            commandLine(shell, "./$script")
        }
    }
}

// copy cmake build library to java resources
tasks.jar {
    dependsOn("buildJNI")
    from("build/cmake/install/ruapu") {
        include("*.dll", "*.so", "*.dylib")
    }
}