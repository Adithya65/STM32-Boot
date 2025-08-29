# Top-level Makefile

BUILD_DIR = build

.PHONY: all cmake $(MAKECMDGOALS)

all:
	@echo "Usage: make <target>"
	@echo "Example: make samples"

cmake:
	@rm -rf $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..

$(MAKECMDGOALS): cmake
	@cd $(BUILD_DIR) && $(MAKE) $(MAKECMDGOALS)

