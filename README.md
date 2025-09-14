# Student Project Template 
## Build & Run
```bash
- `make install` — установка зависимостей
- `make run` — запуск приложения
- `make test` — прогон тестов

## Release workflow
- We keep ONE repository for the whole project.
- At the end of each checkpoint, mark a release tag and add your report.

### Mark a release tag
# end of Release 1:
git tag release-1
git push origin release-1

# end of Release 2:
git tag release-2
git push origin release-2

### Folders for documents
docs/release-1/  # slides, SRS/SDP updates, test report
docs/release-2/
docs/release-3/

```

## Structure
- `src/` : your .c and .h files
- `tests/` : basic test scripts
- `docs/` : Word templates (SRS)
- `reports/` : slides or notes for checkpoints
