

# Register your models here.
from django.contrib import admin
from webapp.models import Category, Page

@admin.register(Category)
class CategoryAdmin(admin.ModelAdmin):
    list_display = ('name', 'visits', 'likes')

@admin.register(Page)
class PageAdmin(admin.ModelAdmin):
    list_display = ('title', 'category', 'url', 'views')
    list_filter = ('category', 'views')
    search_fields = ('title', 'url')
