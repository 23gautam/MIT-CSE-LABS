from django.contrib import admin
import site
from webapp.models import BlogPost
from . import models
from webapp import models

# Register your models here.
class BlogPostAdmin(admin.ModelAdmin):
    list_display = ('title', 'timestamp')
   

admin.site.register(models.BlogPost,BlogPostAdmin) 