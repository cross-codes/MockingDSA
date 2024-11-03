# Compilers
JC = /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.432.b06-1.fc40.x86_64/bin/javac
JAR = /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.432.b06-1.fc40.x86_64/bin/jar

# To be passed as an argument
JAVA_FILE ?= Main.java

CLASS_NAME = $(basename $(notdir $(JAVA_FILE)))
CLASS = Main
JAR_FILE = $(CLASS_NAME).jar
RENAME_JAR_FILE = sol.jar
MANIFEST_FILE = MANIFEST.MF

all: jar

$(CLASS): $(JAVA_FILE)
	$(JC) -d . $(JAVA_FILE)

$(MANIFEST_FILE):
	echo "Main-Class: $(CLASS)" > $(MANIFEST_FILE)

jar: $(CLASS) $(MANIFEST_FILE)
	$(JAR) cfvm $(JAR_FILE) $(MANIFEST_FILE) *.class
	@mv $(JAR_FILE) $(RENAME_JAR_FILE)
	@rm -f *.class $(MANIFEST_FILE)

clean:
	rm $(RENAME_JAR_FILE)